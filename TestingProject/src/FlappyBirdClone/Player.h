#pragma once
#include <Independent.h> 

#include "Color.h"
#include "Random.h"
#include "ParticleSystem.h"

class Player
{
public:
	Player();

	void LoadAssets();

	void OnUpdate(Independent::Timestep ts);
	void OnRender();

	void OnImGuiRender();

	void Reset();

	float GetRotation() const { return m_Velocity.y * 2.0f - 90.0f; }
	const glm::vec2& GetPosition() const { return m_Position; }

	uint32_t GetScore() const { return (uint32_t)(m_Position.x + 10.0f) / 10.0f; }
private:
	glm::vec2 m_Position = { -10.0f, 0.0f };
	glm::vec2 m_Velocity = { 5.0f, 0.0f };

	float m_EnginePower;
	float m_Gravity;

	float m_Time = 0.0f;
	float m_SmokeNextEmitTime = 0.1f;
	float m_SmokeEmitInterval = 0.4f;

	ParticleProps m_SmokeParticle;
	ParticleProps m_EngineParticle;
	ParticleSystem m_ParticleSystem;

	Independent::SharedPtr<Independent::Texture2D> m_ShipTexture;
};