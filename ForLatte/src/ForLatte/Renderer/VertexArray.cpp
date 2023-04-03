#include "flpch.h"

#include "VertexArray.h"
#include "Renderer.h"

#include "ForLatte/Platform/OpenGL/OpenGLVertexArray.h"

namespace ForLatte {
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:   FL_CORE_ASSERT(false, "None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL: return new OpenGLVertexArray();
		}
		FL_CORE_ASSERT(false, "Unknown Renderer API!");
		return nullptr;
	}
}