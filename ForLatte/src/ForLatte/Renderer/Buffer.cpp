#include "flpch.h"
#include "Buffer.h"

#include "Renderer.h"

#include "ForLatte/Platform/OpenGL/OpenGLBuffer.h"

namespace ForLatte {
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None: FL_CORE_ERROR("None is currently not supported!"); return nullptr;
			case RendererAPI::OpenGL: return new OpenGLVertexBuffer(vertices, size);
		}
		FL_CORE_ERROR("Unknown Renderer API!");
		return nullptr;
	}
	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None: FL_CORE_ERROR("None is currently not supported!"); return nullptr;
			case RendererAPI::OpenGL: return new OpenGLIndexBuffer(indices, count);
		}
		FL_CORE_ERROR("Unknown Renderer API!");
		return nullptr;
	}
}
