#pragma once

#include "Independent/Core/include/containers/String.h"
#include "Independent/Core/include/containers/SharedPtr.h"
#include "Independent/Core/include/containers/UnorderedMap.h"

#include <glm/glm.hpp>

namespace Independent {

	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		//TODO: include this function when created complex material system
		//virtual void UploadUniformBuffer() = 0;

		virtual void SetInt(const String& name, int value) = 0;
		virtual void SetFloat3(const String& name, const glm::vec3& value) = 0;
		virtual void SetFloat4(const String& name, const glm::vec4& value) = 0;
		virtual void SetMat4(const String& name, const glm::mat4& value) = 0;

		virtual const String& GetName() const = 0;

		static SharedPtr<Shader> Create(const String& filepath);
		static SharedPtr<Shader> Create(const String& name, const String& vertexSrc, const String& fragmentSrc);
	};

	class ShaderLibrary
	{
	public:
		void Add(const SharedPtr<Shader>& shader);
		void Add(const String& name, const SharedPtr<Shader>& shader);
		SharedPtr<Shader> Load(const String& filepath);
		SharedPtr<Shader> Load(const String& name, const String& filepath);

		SharedPtr<Shader> Get(const String& name);

		bool Exists(const String& name) const;
	private:
		UnorderedMap<String, SharedPtr<Shader>> m_Shaders;
	};
}