#include "flpch.h"
#include "RenderCommand.h"

#include "ForLatte/Platform/OpenGL/OpenGLRendererAPI.h"

namespace ForLatte {
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();
}