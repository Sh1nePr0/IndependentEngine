#pragma once

#include "Independent/Render/include/shader/Shader.h"
#include "Independent/Core/include/containers/UnorderedMap.h"

#include <glm/glm.hpp>

//TODO: REMOVE!
typedef unsigned int GLenum;

namespace Independent {

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const String& filepath);
		OpenGLShader(const String& name, const String& vertexSrc, const String& fragmentSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual void SetInt(const String& name, int value) override;
		virtual void SetIntArray(const String& name, int* values, uint32_t count) override;
		virtual void SetFloat(const String& name, float value) override;
		virtual void SetFloat2(const String& name, const glm::vec2& value) override;
		virtual void SetFloat3(const String& name, const glm::vec3& value) override;
		virtual void SetFloat4(const String& name, const glm::vec4& value) override;
		virtual void SetMat4(const String& name, const glm::mat4& value) override;

		virtual const String& GetName() const override { return m_Name; }

		void UploadUniformInt(const String& name, int value);
		void UploadUniformIntArray(const String& name, int* values, uint32_t count);

		void UploadUniformFloat(const String& name, float value);
		void UploadUniformFloat2(const String& name, const glm::vec2& value);
		void UploadUniformFloat3(const String& name, const glm::vec3& value);
		void UploadUniformFloat4(const String& name, const glm::vec4& value);

		void UploadUniformMat3(const String& name, const glm::mat3& matrix);
		void UploadUniformMat4(const String& name, const glm::mat4& matrix);
	private:
		String ReadFile(const String& filepath);
		UnorderedMap<GLenum, String> PreProcess(const String& source);
		void Compile(const UnorderedMap<GLenum, String>& shaderSources);
	private:
		uint32_t m_RendererID;
		String m_Name;
	};
}