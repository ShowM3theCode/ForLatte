#include "flpch.h"
#include "Texture.h"

#include "Renderer.h"
#include "ForLatte/Platform/OpenGL/OpenGLTexture.h"

namespace ForLatte {

	Ref<Texture2D> Texture2D::Create(int width, int height)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:   FL_CORE_ASSERT(false, "None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL: return CreateRef<OpenGLTexture2D>(width, height);
		}
		FL_CORE_ASSERT(false, "Unknown Renderer API!");
		return nullptr;
	}

	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:   FL_CORE_ASSERT(false, "None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL: return CreateRef<OpenGLTexture2D>(path);
		}
		FL_CORE_ASSERT(false, "Unknown Renderer API!");
		return nullptr;
	}
}