#include "flpch.h"

#include "Renderer.h"
#include "Shader.h"

#include "ForLatte/Platform/OpenGL/OpenGLShader.h"

namespace ForLatte {

	Ref<Shader> Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:   FL_CORE_ASSERT(false, "None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(filepath);
		}
		FL_CORE_ASSERT(false, "Unknown Renderer API!");
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:   FL_CORE_ASSERT(false, "None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(name, vertexSrc, fragmentSrc);
		}
		FL_CORE_ASSERT(false, "Unknown Renderer API!");
		return nullptr;
	}
	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
	{
		FL_CORE_ASSERT(!Exists(name), "Shader already exists!");
		m_Shaders[name] = shader;
	}

	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		auto& name = shader->GetName();
		Add(name, shader);
	}
	Ref<Shader> ShaderLibrary::Load(const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(shader);
		return shader;
	}
	Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(name, shader);
		return shader;
	}
	Ref<Shader> ShaderLibrary::Get(const std::string& name)
	{
		FL_CORE_ASSERT(Exists(name), "Shader not found!");
		return m_Shaders[name];
	}
	bool ShaderLibrary::Exists(const std::string& name) const
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}
}