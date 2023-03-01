#include <ForLatte.h>

class ExampleLayer : public ForLatte::Layer {
public:
	ExampleLayer() : Layer("Example") {}

	void OnUpdate() override {
		FL_INFO("ExampleLayer::Update");
	}

	void OnEvent(ForLatte::Event& event) override {
		FL_TRACE("{0}", event);
	}
};

class Sandbox : public ForLatte::Application {
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
		PushOverlay(new ForLatte::ImGuiLayer());
	}

	~Sandbox() {

	}
};

ForLatte::Application* ForLatte::CreateApplication() {
	return new Sandbox();
}