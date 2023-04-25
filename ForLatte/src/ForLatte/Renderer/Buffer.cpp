#include "flpch.h"
#include "Buffer.h"

#include "Renderer.h"

#include "ForLatte/Platform/OpenGL/OpenGLBuffer.h"

namespace ForLatte {
	Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: FL_CORE_ASSERT(false, "None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL: return CreateRef<OpenGLVertexBuffer>(size);
		}
		FL_CORE_ASSERT(false, "Unknown Renderer API!");
		return nullptr;
	}
	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: FL_CORE_ASSERT(false, "None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL: return CreateRef<OpenGLVertexBuffer>(vertices, size);
		}
		FL_CORE_ASSERT(false, "Unknown Renderer API!");
		return nullptr;
	}
	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: FL_CORE_ASSERT(false, "None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL: return CreateRef<OpenGLIndexBuffer>(indices, count);
		}
		FL_CORE_ASSERT(false, "Unknown Renderer API!");
		return nullptr;
	}
}
