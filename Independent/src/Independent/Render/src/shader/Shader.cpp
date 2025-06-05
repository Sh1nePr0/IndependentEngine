#include "idpdpch.h"
#include "Independent/Render/include/shader/Shader.h"

#include "Independent/Render/include/Renderer.h"
#include "Platform/OpenGL/include/OpenGLShader.h"

namespace Independent {

	SharedPtr<Shader> Shader::Create(const String& filepath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:     IDPD_CORE_ASSERT(false, "RendererAPI::None is currrently not supported"); return nullptr;
		case RendererAPI::API::OpenGL:   return std::make_shared<OpenGLShader>(filepath);
		}

		IDPD_CORE_ASSERT(false, "Unknown RendereAPI");
		return nullptr;
	}

	SharedPtr<Shader> Shader::Create(const String& name, const String& vertexSrc, const String& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:     IDPD_CORE_ASSERT(false, "RendererAPI::None is currrently not supported"); return nullptr;
		case RendererAPI::API::OpenGL:   return std::make_shared<OpenGLShader>(name, vertexSrc, fragmentSrc);
		}

		IDPD_CORE_ASSERT(false, "Unknown RendereAPI");
		return nullptr;
	}
	
	void ShaderLibrary::Add(const SharedPtr<Shader>& shader)
	{
		auto& name = shader->GetName();
		Add(name, shader);
	}

	void ShaderLibrary::Add(const String& name, const SharedPtr<Shader>& shader)
	{
		IDPD_CORE_ASSERT(!Exists(name), "Shader already exists!");
		m_Shaders[name] = shader;
	}

	SharedPtr<Shader> ShaderLibrary::Load(const String& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(shader);
		return shader;
	}

	SharedPtr<Shader> ShaderLibrary::Load(const String& name, const String& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(name, shader);
		return shader;
	}

	SharedPtr<Shader> ShaderLibrary::Get(const String& name)
	{
		IDPD_CORE_ASSERT(Exists(name), "Shader not found!");
		return m_Shaders[name];
	}

	bool ShaderLibrary::Exists(const String& name) const
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}

}