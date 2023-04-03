#include <ForLatte.h>

#include "ForLatte/Platform/OpenGL/OpenGLShader.h"

#include "../imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class ExampleLayer : public ForLatte::Layer {
public:
	ExampleLayer()
		: Layer("Example"), m_CameraController(1280.0f / 720.0f, true)
	{
		m_VertexArray.reset(ForLatte::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		std::shared_ptr<ForLatte::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(ForLatte::VertexBuffer::Create(vertices, sizeof(vertices)));
		ForLatte::BufferLayout layout = {
			{ ForLatte::ShaderDataType::Float3, "a_Position" },
			{ ForLatte::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<ForLatte::IndexBuffer> indexBuffer;
		indexBuffer.reset(ForLatte::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(ForLatte::VertexArray::Create());

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		std::shared_ptr<ForLatte::VertexBuffer> squareVB;
		squareVB.reset(ForLatte::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ ForLatte::ShaderDataType::Float3, "a_Position" },
			{ ForLatte::ShaderDataType::Float2, "a_TexCoord" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<ForLatte::IndexBuffer> squareIB;
		squareIB.reset(ForLatte::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader = ForLatte::Shader::Create("VertexPosColor", vertexSrc, fragmentSrc);

		std::string flatColorShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

		m_FlatColorShader = ForLatte::Shader::Create("FlatColor", flatColorShaderVertexSrc, flatColorShaderFragmentSrc);
	
		std::string textureShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec2 a_TexCoord;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec2 v_TexCoord;
			

			void main()
			{
				v_TexCoord = a_TexCoord;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string textureShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec2 v_TexCoord;

			uniform sampler2D u_Texture;

			void main()
			{
				color = texture(u_Texture, v_TexCoord);
			}
		)";

		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

		m_Texture = ForLatte::Texture2D::Create("assets/textures/checkerboard.png");
		m_ChernoLogoTexture = ForLatte::Texture2D::Create("assets/textures/ChernoLogo.png");
	
		std::dynamic_pointer_cast<ForLatte::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<ForLatte::OpenGLShader>(textureShader)
			->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(ForLatte::Timestep ts) override
	{

		m_CameraController.OnUpdate(ts);

		ForLatte::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		ForLatte::RenderCommand::Clear();

		ForLatte::Renderer::BeginScene(m_CameraController.GetCamera());

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		glm::vec4 redColor(0.8f, 0.2f, 0.3f, 1.0f);
		glm::vec4 blueColor(0.2f, 0.3f, 0.8f, 1.0f);

		std::dynamic_pointer_cast<ForLatte::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<ForLatte::OpenGLShader>(m_FlatColorShader)
			->UploadUniformFloat3("u_Color", m_SquareColor);
		
		for (int y = 0; y < 20; y++) {
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;

				ForLatte::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}

		auto textureShader = m_ShaderLibrary.Get("Texture");

		m_Texture->Bind();
		ForLatte::Renderer::Submit(textureShader, m_SquareVA,
			glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		m_ChernoLogoTexture->Bind();
		ForLatte::Renderer::Submit(textureShader, m_SquareVA,
			glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		// Triangle 
		// ForLatte::Renderer::Submit(m_Shader, m_VertexArray);

		ForLatte::Renderer::EndScene();
	}

	void OnEvent(ForLatte::Event& e) override
	{
		m_CameraController.OnEvent(e);
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

private:
	ForLatte::ShaderLibrary m_ShaderLibrary;

	ForLatte::Ref<ForLatte::Shader> m_Shader;
	ForLatte::Ref<ForLatte::VertexArray> m_VertexArray;

	ForLatte::Ref<ForLatte::Shader> m_FlatColorShader;
	ForLatte::Ref<ForLatte::VertexArray> m_SquareVA;

	ForLatte::Ref<ForLatte::Texture2D> m_Texture, m_ChernoLogoTexture;

	ForLatte::OrthographicCameraController m_CameraController;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};

class Sandbox : public ForLatte::Application {
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

ForLatte::Application* ForLatte::CreateApplication()
{
	return new Sandbox();
}