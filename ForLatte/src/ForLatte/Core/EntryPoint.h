#pragma once

#ifdef FL_PLATFORM_WINDOWS

extern ForLatte::Application* ForLatte::CreateApplication();

void main(int argc, char** argv) {
	ForLatte::Log::Init();
	FL_CORE_WARN("Initialize log...");
	char a[] = "Welcome to ForLatte 2023!";
	FL_INFO("{0}", a);
	auto app = ForLatte::CreateApplication();
	app->Run();
	delete app;
}

#endif