#include "idpdpch.h"

#include "Independent/Render/include/Renderer2D.h"
#include "Independent/Render/include/vertex_array/VertexArray.h"
#include "Independent/Render/include/shader/Shader.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Independent {

	struct QuadVertex
	{
		glm::vec3 Position;
		glm::vec2 TexCoord;
		glm::vec4 Color;
		float TextureIndex;
		float TilingFactor;
	};

	struct Renderer2DData
	{
		const uint32_t MaxQuads = 10000;
		const uint32_t MaxVertices = MaxQuads * 4;
		const uint32_t MaxIndices = MaxQuads * 6;
		static const uint32_t MaxTextureSlots = 32; // TODO: Render capabilities

		SharedPtr<VertexArray> QuadVertexArray;
		SharedPtr<VertexBuffer> QuadVertexBuffer;
		SharedPtr<Shader> TextureShader;
		SharedPtr<Texture2D> WhiteTexture;

		uint32_t QuadIndexCount = 0;

		QuadVertex* QuadVertexBufferBase = nullptr;
		QuadVertex* QuadVertexBufferPtr = nullptr;

		std::array<SharedPtr<Texture2D>, MaxTextureSlots> TextureSlots;
		uint32_t TextureSlotIndex = 1; // 0 = white texture

		glm::vec4 QuadVertexPositions[4];
	};

	static Renderer2DData s_Renderer2DData;

	void Renderer2D::Init()
	{
		IDPD_PROFILE_FUNCTION();

		s_Renderer2DData.QuadVertexArray = VertexArray::Create();

		s_Renderer2DData.QuadVertexBuffer = VertexBuffer::Create(s_Renderer2DData.MaxVertices * sizeof(QuadVertex));
		{
			BufferLayout quadVBOLayout = {
				{ ShaderDataType::Float3, "a_Position" },
				{ ShaderDataType::Float2, "a_TextureCoord" },
				{ ShaderDataType::Float4, "a_Color" },
				{ ShaderDataType::Float, "a_TextureIndex" },
				{ ShaderDataType::Float, "a_TilingFactor" }
			};

			s_Renderer2DData.QuadVertexBuffer->SetLayout(quadVBOLayout);
		}
		s_Renderer2DData.QuadVertexArray->AddVertexBuffer(s_Renderer2DData.QuadVertexBuffer);

		s_Renderer2DData.QuadVertexBufferBase = new QuadVertex[s_Renderer2DData.MaxVertices];

		uint32_t* quadIndices = new uint32_t[s_Renderer2DData.MaxIndices];

		uint32_t offset = 0;
		for (uint32_t i = 0; i < s_Renderer2DData.MaxIndices; i += 6)
		{
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;

			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;

			offset += 4;
		}

		SharedPtr<IndexBuffer> quadIBO = IndexBuffer::Create(quadIndices, s_Renderer2DData.MaxIndices);
		s_Renderer2DData.QuadVertexArray->SetIndexBuffer(quadIBO);
		delete[] quadIndices;

		s_Renderer2DData.WhiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		s_Renderer2DData.WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

		int32_t samplers[s_Renderer2DData.MaxTextureSlots];
		for (uint32_t i = 0; i < s_Renderer2DData.MaxTextureSlots; i++)
			samplers[i] = i;

//TODO: Remove this shit!
#define IDPD_FLAPPY_BIRD_CLONE_SHADER 0
#if		IDPD_FLAPPY_BIRD_CLONE_SHADER 
		s_Renderer2DData.TextureShader = Shader::Create("assets/shaders/FlappyBirdCloneShader.glsl");
#else 
		s_Renderer2DData.TextureShader = Shader::Create("assets/shaders/Texture.glsl");
#endif

		s_Renderer2DData.TextureShader->Bind();
		s_Renderer2DData.TextureShader->SetIntArray("u_Textures",  samplers, s_Renderer2DData.MaxTextureSlots);

		s_Renderer2DData.TextureSlots[0] = s_Renderer2DData.WhiteTexture;

		s_Renderer2DData.QuadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
		s_Renderer2DData.QuadVertexPositions[1] = { 0.5f, -0.5f, 0.0f, 1.0f };
		s_Renderer2DData.QuadVertexPositions[2] = { 0.5f, 0.5f, 0.0f, 1.0f };
		s_Renderer2DData.QuadVertexPositions[3] = { -0.5f, 0.5f, 0.0f, 1.0f };
	}

	void Renderer2D::Shutdown()
	{
		IDPD_PROFILE_FUNCTION();
	}

	void Renderer2D::BeginScene(const SharedPtr<CameraBase>& camera)
	{
		IDPD_PROFILE_FUNCTION();

		s_Renderer2DData.TextureShader->Bind();
		s_Renderer2DData.TextureShader->SetMat4("u_ViewProjection", camera->GetViewProjectionMatrix());

		s_Renderer2DData.QuadIndexCount = 0;
		s_Renderer2DData.QuadVertexBufferPtr = s_Renderer2DData.QuadVertexBufferBase;

		s_Renderer2DData.TextureSlotIndex = 1;
	}

	void Renderer2D::EndScene()
	{
		IDPD_PROFILE_FUNCTION();

		uint32_t dataSize = (uint8_t*)s_Renderer2DData.QuadVertexBufferPtr - (uint8_t*)s_Renderer2DData.QuadVertexBufferBase;
		s_Renderer2DData.QuadVertexBuffer->SetData(s_Renderer2DData.QuadVertexBufferBase, dataSize);

		Flush();
	}

	void Renderer2D::Flush()
	{
		//Bind Textures
		for (uint32_t i = 0; i < s_Renderer2DData.TextureSlotIndex; i++)
			s_Renderer2DData.TextureSlots[i]->Bind(i);

		RenderCommand::DrawIndexed(s_Renderer2DData.QuadVertexArray, s_Renderer2DData.QuadIndexCount);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		IDPD_PROFILE_FUNCTION();

		const float textureIndex = 0.0f; //White texture
		const float tilingFactor = 1.0f;

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		s_Renderer2DData.QuadVertexBufferPtr->Position = transform * s_Renderer2DData.QuadVertexPositions[0];
		s_Renderer2DData.QuadVertexBufferPtr->Color = color;
		s_Renderer2DData.QuadVertexBufferPtr->TexCoord = { 0.0f, 0.0f };
		s_Renderer2DData.QuadVertexBufferPtr->TextureIndex = textureIndex;
		s_Renderer2DData.QuadVertexBufferPtr->TilingFactor = tilingFactor;
		s_Renderer2DData.QuadVertexBufferPtr++;

		s_Renderer2DData.QuadVertexBufferPtr->Position = transform * s_Renderer2DData.QuadVertexPositions[1];
		s_Renderer2DData.QuadVertexBufferPtr->Color = color;
		s_Renderer2DData.QuadVertexBufferPtr->TexCoord = { 1.0f, 0.0f };
		s_Renderer2DData.QuadVertexBufferPtr->TextureIndex = textureIndex;
		s_Renderer2DData.QuadVertexBufferPtr->TilingFactor = tilingFactor;
		s_Renderer2DData.QuadVertexBufferPtr++;

		s_Renderer2DData.QuadVertexBufferPtr->Position = transform * s_Renderer2DData.QuadVertexPositions[2];
		s_Renderer2DData.QuadVertexBufferPtr->Color = color;
		s_Renderer2DData.QuadVertexBufferPtr->TexCoord = { 1.0f, 1.0f };
		s_Renderer2DData.QuadVertexBufferPtr->TextureIndex = textureIndex;
		s_Renderer2DData.QuadVertexBufferPtr->TilingFactor = tilingFactor;
		s_Renderer2DData.QuadVertexBufferPtr++;

		s_Renderer2DData.QuadVertexBufferPtr->Position = transform * s_Renderer2DData.QuadVertexPositions[3];
		s_Renderer2DData.QuadVertexBufferPtr->Color = color;
		s_Renderer2DData.QuadVertexBufferPtr->TexCoord = { 0.0f, 1.0f };
		s_Renderer2DData.QuadVertexBufferPtr->TextureIndex = textureIndex;
		s_Renderer2DData.QuadVertexBufferPtr->TilingFactor = tilingFactor;
		s_Renderer2DData.QuadVertexBufferPtr++;

		s_Renderer2DData.QuadIndexCount += 6;
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const SharedPtr<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
	{																										
		DrawQuad({ position.x, position.y, 0.0f }, size, texture, tilingFactor, tintColor);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const SharedPtr<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
	{
		IDPD_PROFILE_FUNCTION();

		constexpr glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f };

		float textureIndex = 0.0f;
		for (uint32_t i = 1; i < s_Renderer2DData.TextureSlotIndex; i++)
		{
			if (*s_Renderer2DData.TextureSlots[i].get() == *texture.get())
			{
				textureIndex = (float)i;
				break;
			}
		}

		if (textureIndex == 0.0f)
		{
			textureIndex = (float)s_Renderer2DData.TextureSlotIndex;
			s_Renderer2DData.TextureSlots[s_Renderer2DData.TextureSlotIndex] = texture;
			s_Renderer2DData.TextureSlotIndex++;
		}

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		s_Renderer2DData.QuadVertexBufferPtr->Position = transform * s_Renderer2DData.QuadVertexPositions[0];
		s_Renderer2DData.QuadVertexBufferPtr->Color = color;
		s_Renderer2DData.QuadVertexBufferPtr->TexCoord = { 0.0f, 0.0f };
		s_Renderer2DData.QuadVertexBufferPtr->TextureIndex = textureIndex;
		s_Renderer2DData.QuadVertexBufferPtr->TilingFactor = tilingFactor;
		s_Renderer2DData.QuadVertexBufferPtr++;

		s_Renderer2DData.QuadVertexBufferPtr->Position = transform * s_Renderer2DData.QuadVertexPositions[1];
		s_Renderer2DData.QuadVertexBufferPtr->Color = color;
		s_Renderer2DData.QuadVertexBufferPtr->TexCoord = { 1.0f, 0.0f };
		s_Renderer2DData.QuadVertexBufferPtr->TextureIndex = textureIndex;
		s_Renderer2DData.QuadVertexBufferPtr->TilingFactor = tilingFactor;
		s_Renderer2DData.QuadVertexBufferPtr++;

		s_Renderer2DData.QuadVertexBufferPtr->Position = transform * s_Renderer2DData.QuadVertexPositions[2];
		s_Renderer2DData.QuadVertexBufferPtr->Color = color;
		s_Renderer2DData.QuadVertexBufferPtr->TexCoord = { 1.0f, 1.0f };
		s_Renderer2DData.QuadVertexBufferPtr->TextureIndex = textureIndex;
		s_Renderer2DData.QuadVertexBufferPtr->TilingFactor = tilingFactor;
		s_Renderer2DData.QuadVertexBufferPtr++;

		s_Renderer2DData.QuadVertexBufferPtr->Position = transform * s_Renderer2DData.QuadVertexPositions[3];
		s_Renderer2DData.QuadVertexBufferPtr->Color = color;
		s_Renderer2DData.QuadVertexBufferPtr->TexCoord = { 0.0f, 1.0f };
		s_Renderer2DData.QuadVertexBufferPtr->TextureIndex = textureIndex;
		s_Renderer2DData.QuadVertexBufferPtr->TilingFactor = tilingFactor;
		s_Renderer2DData.QuadVertexBufferPtr++;

		s_Renderer2DData.QuadIndexCount += 6;
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, color);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		IDPD_PROFILE_FUNCTION();

		const float textureIndex = 0.0f; //White texture
		const float tilingFactor = 1.0f;

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		s_Renderer2DData.QuadVertexBufferPtr->Position = transform * s_Renderer2DData.QuadVertexPositions[0];
		s_Renderer2DData.QuadVertexBufferPtr->Color = color;
		s_Renderer2DData.QuadVertexBufferPtr->TexCoord = { 0.0f, 0.0f };
		s_Renderer2DData.QuadVertexBufferPtr->TextureIndex = textureIndex;
		s_Renderer2DData.QuadVertexBufferPtr->TilingFactor = tilingFactor;
		s_Renderer2DData.QuadVertexBufferPtr++;

		s_Renderer2DData.QuadVertexBufferPtr->Position = transform * s_Renderer2DData.QuadVertexPositions[1];
		s_Renderer2DData.QuadVertexBufferPtr->Color = color;
		s_Renderer2DData.QuadVertexBufferPtr->TexCoord = { 1.0f, 0.0f };
		s_Renderer2DData.QuadVertexBufferPtr->TextureIndex = textureIndex;
		s_Renderer2DData.QuadVertexBufferPtr->TilingFactor = tilingFactor;
		s_Renderer2DData.QuadVertexBufferPtr++;

		s_Renderer2DData.QuadVertexBufferPtr->Position = transform * s_Renderer2DData.QuadVertexPositions[2];
		s_Renderer2DData.QuadVertexBufferPtr->Color = color;
		s_Renderer2DData.QuadVertexBufferPtr->TexCoord = { 1.0f, 1.0f };
		s_Renderer2DData.QuadVertexBufferPtr->TextureIndex = textureIndex;
		s_Renderer2DData.QuadVertexBufferPtr->TilingFactor = tilingFactor;
		s_Renderer2DData.QuadVertexBufferPtr++;

		s_Renderer2DData.QuadVertexBufferPtr->Position = transform * s_Renderer2DData.QuadVertexPositions[3];
		s_Renderer2DData.QuadVertexBufferPtr->Color = color;
		s_Renderer2DData.QuadVertexBufferPtr->TexCoord = { 0.0f, 1.0f };
		s_Renderer2DData.QuadVertexBufferPtr->TextureIndex = textureIndex;
		s_Renderer2DData.QuadVertexBufferPtr->TilingFactor = tilingFactor;
		s_Renderer2DData.QuadVertexBufferPtr++;

		s_Renderer2DData.QuadIndexCount += 6;
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const SharedPtr<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
	{
		DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, texture, tilingFactor, tintColor);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const SharedPtr<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
	{
		IDPD_PROFILE_FUNCTION();

		constexpr glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f };

		float textureIndex = 0.0f;
		for (uint32_t i = 1; i < s_Renderer2DData.TextureSlotIndex; i++)
		{
			if (*s_Renderer2DData.TextureSlots[i].get() == *texture.get())
			{
				textureIndex = (float)i;
				break;
			}
		}

		if (textureIndex == 0.0f)
		{
			textureIndex = (float)s_Renderer2DData.TextureSlotIndex;
			s_Renderer2DData.TextureSlots[s_Renderer2DData.TextureSlotIndex] = texture;
			s_Renderer2DData.TextureSlotIndex++;
		}

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		s_Renderer2DData.QuadVertexBufferPtr->Position = transform * s_Renderer2DData.QuadVertexPositions[0];
		s_Renderer2DData.QuadVertexBufferPtr->Color = color;
		s_Renderer2DData.QuadVertexBufferPtr->TexCoord = { 0.0f, 0.0f };
		s_Renderer2DData.QuadVertexBufferPtr->TextureIndex = textureIndex;
		s_Renderer2DData.QuadVertexBufferPtr->TilingFactor = tilingFactor;
		s_Renderer2DData.QuadVertexBufferPtr++;

		s_Renderer2DData.QuadVertexBufferPtr->Position = transform * s_Renderer2DData.QuadVertexPositions[1];
		s_Renderer2DData.QuadVertexBufferPtr->Color = color;
		s_Renderer2DData.QuadVertexBufferPtr->TexCoord = { 1.0f, 0.0f };
		s_Renderer2DData.QuadVertexBufferPtr->TextureIndex = textureIndex;
		s_Renderer2DData.QuadVertexBufferPtr->TilingFactor = tilingFactor;
		s_Renderer2DData.QuadVertexBufferPtr++;

		s_Renderer2DData.QuadVertexBufferPtr->Position = transform * s_Renderer2DData.QuadVertexPositions[2];
		s_Renderer2DData.QuadVertexBufferPtr->Color = color;
		s_Renderer2DData.QuadVertexBufferPtr->TexCoord = { 1.0f, 1.0f };
		s_Renderer2DData.QuadVertexBufferPtr->TextureIndex = textureIndex;
		s_Renderer2DData.QuadVertexBufferPtr->TilingFactor = tilingFactor;
		s_Renderer2DData.QuadVertexBufferPtr++;

		s_Renderer2DData.QuadVertexBufferPtr->Position = transform * s_Renderer2DData.QuadVertexPositions[3];
		s_Renderer2DData.QuadVertexBufferPtr->Color = color;
		s_Renderer2DData.QuadVertexBufferPtr->TexCoord = { 0.0f, 1.0f };
		s_Renderer2DData.QuadVertexBufferPtr->TextureIndex = textureIndex;
		s_Renderer2DData.QuadVertexBufferPtr->TilingFactor = tilingFactor;
		s_Renderer2DData.QuadVertexBufferPtr++;

		s_Renderer2DData.QuadIndexCount += 6;
	}

}