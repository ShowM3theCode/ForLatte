#include <ForLatte.h>

class Sandbox : public ForLatte::Application {
public:
	Sandbox() {

	}

	~Sandbox() {

	}
};

ForLatte::Application* ForLatte::CreateApplication() {
	return new Sandbox();
}