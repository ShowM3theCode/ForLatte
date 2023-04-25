#pragma once
#include "ForLatte/Renderer/Texture.h"

#include <glad/glad.h>

namespace ForLatte {

	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string& path);

		OpenGLTexture2D(int width, int height);

		virtual ~OpenGLTexture2D();

		virtual uint32_t GetWidth() const { return m_Width; }
		virtual uint32_t GetHeight() const { return m_Height; }

		virtual void SetData(void* data, uint32_t size) override;

		virtual void Bind(uint32_t slot = 0) const override;

		virtual bool operator==(const Texture2D& other) const override;

	private:
		std::string m_Path;
		uint32_t m_RendererID, m_Width, m_Height;
		GLenum m_InternalFormat, m_DataFormat;
	};

}