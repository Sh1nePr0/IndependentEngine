#pragma once

#include "Independent/Render/include/vertex_array/VertexArray.h"
#include "Independent/Core/include/containers/SharedPtr.h"
#include "Independent/Core/include/containers/Vector.h"

namespace Independent {

	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();


		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(const SharedPtr<VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const SharedPtr<IndexBuffer>& indexBuffer) override;

		virtual const Vector<SharedPtr<VertexBuffer>>& GetVertexBuffers() const override { return m_VertexBuffers; }
		virtual const SharedPtr<IndexBuffer>& GetIndexBuffer() const override { return m_IndexBuffer; }
	private:
		uint32_t m_RendererID;
		Vector<SharedPtr<VertexBuffer>> m_VertexBuffers;
		SharedPtr<IndexBuffer> m_IndexBuffer;
	};

}