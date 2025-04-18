#include "Level.h"
#include "Color.h"

#include <glm/gtc/matrix_transform.hpp>

static glm::vec4 HSVtoRGB(const glm::vec3& hsv) {
	int H = (int)(hsv.x * 360.0f);
	double S = hsv.y;
	double V = hsv.z;

	double C = S * V;
	double X = C * (1 - abs(fmod(H / 60.0, 2) - 1));
	double m = V - C;
	double Rs, Gs, Bs;

	if (H >= 0 && H < 60) {
		Rs = C;
		Gs = X;
		Bs = 0;
	}
	else if (H >= 60 && H < 120) {
		Rs = X;
		Gs = C;
		Bs = 0;
	}
	else if (H >= 120 && H < 180) {
		Rs = 0;
		Gs = C;
		Bs = X;
	}
	else if (H >= 180 && H < 240) {
		Rs = 0;
		Gs = X;
		Bs = C;
	}
	else if (H >= 240 && H < 300) {
		Rs = X;
		Gs = 0;
		Bs = C;
	}
	else {
		Rs = C;
		Gs = 0;
		Bs = X;
	}

	return { (Rs + m), (Gs + m), (Bs + m), 1.0f };
}

static bool PointInTriangle(const glm::vec2& p, const glm::vec2& p0, const glm::vec2& p1, const glm::vec2& p2)
{
	float s = p0.y * p2.x - p0.x * p2.y + (p2.y - p0.y) * p.x + (p0.x - p2.x) * p.y;
	float t = p0.x * p1.y - p0.y * p1.x + (p0.y - p1.y) * p.x + (p1.x - p0.x) * p.y;

	if ((s < 0) != (t < 0))
		return false;

	float A = -p1.y * p2.x + p0.y * (p2.x - p1.x) + p0.x * (p1.y - p2.y) + p1.x * p2.y;

	return A < 0 ?
		(s <= 0 && s + t >= A) :
		(s >= 0 && s + t <= A);
}


Level::Level()
{

}

void Level::Init()
{ 
	m_TriangleTexture = Independent::Texture2D::Create("assets/textures/Triangle.png");
	m_Player.LoadAssets();

	m_Pillars.resize(5);
	for (int i = 0; i < 5; i++)
		CreatePillar(i, i * 10.0f);
}

void Level::OnUpdate(Independent::Timestep ts)
{
	m_Player.OnUpdate(ts);

	if (CollisionTest())
	{
		GameOver();
		return;
	}

	m_PillarsHSV.x += 0.1f * ts;
	if (m_PillarsHSV.x >= 1.0f)
		m_PillarsHSV.x = 0.0f;

	if (m_Player.GetPosition().x > m_PillarTarget)
	{
		CreatePillar(m_PillarIndex, m_PillarTarget + 20.0f);
		m_PillarIndex = ++m_PillarIndex % m_Pillars.size();
		m_PillarTarget += 10.0f;
	}
}

void Level::OnRender()
{
	const glm::vec2& playerPos = m_Player.GetPosition();

	glm::vec4 color = HSVtoRGB(m_PillarsHSV);

	//Background
	Independent::Renderer2D::DrawQuad({ playerPos.x, 0.0f, -0.8f }, { 50.0f, 50.0f }, { 0.3f, 0.3f, 0.3f, 1.0f });

	//Floor and ceiling
	Independent::Renderer2D::DrawQuad({ playerPos.x, 34.0f  }, { 50.0f, 50.0f }, color);
	Independent::Renderer2D::DrawQuad({ playerPos.x, -34.0f }, { 50.0f, 50.0f }, color);

	
	for (Pillar& pillar : m_Pillars)
	{
		Independent::Renderer2D::DrawRotatedQuad(pillar.TopPosition, pillar.TopScale,glm::radians(180.0f), m_TriangleTexture, 1.0f, color);
		Independent::Renderer2D::DrawRotatedQuad(pillar.BottomPosition, pillar.BottomScale, 0.0f, m_TriangleTexture, 1.0f, color);
	}

	m_Player.OnRender();

	//for (glm::vec2& p : m_Points)
	//{
	//	Independent::Renderer2D::DrawQuad({p.x, p.y, 0.5f}, {0.4f, 0.4f}, Color::Red);
	//}

	m_Points.clear();
}

void Level::OnImGuiRender()
{
	m_Player.OnImGuiRender();
}

void Level::CreatePillar(int index, float offset)
{
	Pillar& pillar = m_Pillars[index];
	pillar.TopPosition.x = offset;
	pillar.BottomPosition.x = offset;

	pillar.TopPosition.z = index * 0.1f - 0.5f;
	pillar.BottomPosition.z = index * 0.1f - 0.5f;

	float center = Random::Float() * 5.0f - 2.5f;
	float gap = Random::Float() * 3.0f - 1.5f;

	pillar.TopPosition.y = 10.0f + center + gap * 0.5f;
	pillar.BottomPosition.y = -10.0f + center + gap * 0.5f;
}

bool Level::CollisionTest()
{
	glm::vec4 playerVertices[4] = {
		{-0.5f, -0.5f, 0.0f, 1.0f },
		{ 0.5f, -0.5f, 0.0f, 1.0f },
		{ 0.5f,  0.5f, 0.0f, 1.0f },
		{ -0.5f,  0.5f, 0.0f, 1.0f}
	};

	const glm::vec2& pos = m_Player.GetPosition();
	glm::vec4 playerTransformedVerts[4];
	for (int i = 0; i < 4; i++)
	{
		playerTransformedVerts[i] = glm::translate(glm::mat4(1.0f), { pos.x, pos.y, 0.0f })
			* glm::rotate(glm::mat4(1.0f), glm::radians(m_Player.GetRotation()), { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { 0.77f, 1.23f, 1.0f })
			* playerVertices[i];

		m_Points.emplace_back(playerTransformedVerts[i].x, playerTransformedVerts[i].y);
	}

	

	//To match Triangle.png (each corner is 5% from the texture edge)
	glm::vec4 pillarVertices[3] = {
		{-0.5f + 0.05f, -0.5f + 0.05f, 0.0f, 1.0f },
		{ 0.5f - 0.05f, -0.5f + 0.05f, 0.0f, 1.0f },
		{ 0.0f + 0.0f,  0.5f - 0.05f, 0.0f, 1.0f }
	};

	for (Pillar& p : m_Pillars)
	{
		glm::vec2 triangle[3];

		//Top pillars
		for (int i = 0; i < 3; i++)
		{
			triangle[i] = glm::translate(glm::mat4(1.0f), { p.TopPosition.x, p.TopPosition.y, 0.0f })
				* glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), { 0.0f, 0.0f, 1.0f })
				* glm::scale(glm::mat4(1.0f), { p.TopScale.x, p.TopScale.y, 1.0f })
				* pillarVertices[i];

			m_Points.emplace_back(triangle[i].x, triangle[i].y);
		}

		//Check here
		for (glm::vec4& vert : playerTransformedVerts)
		{
			if (PointInTriangle({ vert.x, vert.y }, triangle[0], triangle[1], triangle[2]))
				return true;
		}

		//Bottom pillars
		for (int i = 0; i < 3; i++)
		{
			triangle[i] = glm::translate(glm::mat4(1.0f), { p.BottomPosition.x, p.BottomPosition.y, 0.0f })
				* glm::scale(glm::mat4(1.0f), { p.BottomScale.x, p.BottomScale.y, 1.0f })
				* pillarVertices[i];

			m_Points.emplace_back(triangle[i].x, triangle[i].y);
		}

		//Check here
		for (glm::vec4& vert : playerTransformedVerts)
		{
			if (PointInTriangle({ vert.x, vert.y }, triangle[0], triangle[1], triangle[2]))
				return true;
		}
		
	}

	return false;
}

void Level::GameOver()
{
	m_GameOver = true;
}

void Level::Reset()
{
	m_GameOver = false;

	m_Player.Reset();

	m_PillarTarget = 30.0f;
	m_PillarIndex = 0;
	for (int i = 0; i < 5; i++)
		CreatePillar(i, i * 10.0f);
}