#include <ForLatte.h>

#include "../imgui/imgui.h"


class ExampleLayer : public ForLatte::Layer {
public:
	ExampleLayer() : Layer("Example") {
	}

	void OnUpdate() override {
	}

	void OnEvent(ForLatte::Event& event) override {
		// FL_TRACE("{0}", event);
	}

	virtual void OnImGuiRender() override {
		ImGui::Begin("test");
		ImGui::Text("Hello World!");
		ImGui::End();
	}

};

class Sandbox : public ForLatte::Application {
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
	}

	~Sandbox() {

	}
};

ForLatte::Application* ForLatte::CreateApplication() {
	return new Sandbox();
}