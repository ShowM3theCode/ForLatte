#pragma once

#ifdef FL_PLATFORM_WINDOWS

extern ForLatte::Application* ForLatte::CreateApplication();

void main(int argc, char** argv) {
	printf("Welcome to ForLatte Engine...");
	auto app = ForLatte::CreateApplication();
	app->Run();
	delete app;
}

#endif