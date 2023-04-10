#pragma once

#include "ForLatte.h"

class Sandbox2D : public ForLatte::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;
	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(ForLatte::Timestep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(ForLatte::Event& e) override;

private:
	ForLatte::OrthographicCameraController m_CameraController;

	ForLatte::Ref<ForLatte::VertexArray> m_SquareVA;
	ForLatte::Ref<ForLatte::Shader> m_FlatColorShader;

	ForLatte::Ref<ForLatte::Texture2D> m_CheckerboardTexture;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};
