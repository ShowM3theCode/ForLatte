#include <ForLatte.h>

#include "../imgui/imgui.h"


class ExampleLayer : public ForLatte::Layer {
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
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

		float squareVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};

		std::shared_ptr<ForLatte::VertexBuffer> squareVB;
		squareVB.reset(ForLatte::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ ForLatte::ShaderDataType::Float3, "a_Position" }
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

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);	
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

		m_Shader.reset(new ForLatte::Shader(vertexSrc, fragmentSrc));

		std::string blueShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);	
			}
		)";

		std::string blueShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

		m_BlueShader.reset(new ForLatte::Shader(blueShaderVertexSrc, blueShaderFragmentSrc));
	}

	void OnUpdate() override
	{
		if (ForLatte::Input::IsKeyPressed(FL_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed;
		else if (ForLatte::Input::IsKeyPressed(FL_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed;

		if (ForLatte::Input::IsKeyPressed(FL_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed;
		else if (ForLatte::Input::IsKeyPressed(FL_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed;

		if (ForLatte::Input::IsKeyPressed(FL_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed;
		else if (ForLatte::Input::IsKeyPressed(FL_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed;

		ForLatte::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		ForLatte::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		ForLatte::Renderer::BeginScene(m_Camera);

		ForLatte::Renderer::Submit(m_BlueShader, m_SquareVA);
		ForLatte::Renderer::Submit(m_Shader, m_VertexArray);

		ForLatte::Renderer::EndScene();
	}

	void OnEvent(ForLatte::Event& event) override
	{

	}

	virtual void OnImGuiRender() override
	{

	}

private:
	std::shared_ptr<ForLatte::Shader> m_Shader;
	std::shared_ptr<ForLatte::VertexArray> m_VertexArray;

	std::shared_ptr<ForLatte::Shader> m_BlueShader;
	std::shared_ptr<ForLatte::VertexArray> m_SquareVA;

	ForLatte::OrthoGraphicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 0.1f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 1.0f;
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