#pragma once

#include <memory>
#include "Independent/Render/include/buffer/Buffer.h"
#include "Independent/Core/include/containers/Vector.h"
#include "Independent/Core/include/containers/SharedPtr.h"

namespace Independent {

	class VertexArray
	{
	public:
		virtual ~VertexArray() {}


		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const SharedPtr<VertexBuffer>& vertexBuffer) = 0;
		virtual void SetIndexBuffer(const SharedPtr<IndexBuffer>& indexBuffer) = 0;

		virtual const Vector<SharedPtr<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const SharedPtr<IndexBuffer>& GetIndexBuffer() const = 0;

		static SharedPtr<VertexArray> Create();
	};

}