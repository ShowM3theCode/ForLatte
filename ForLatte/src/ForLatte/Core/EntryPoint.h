#pragma once

#ifdef FL_PLATFORM_WINDOWS

extern ForLatte::Application* ForLatte::CreateApplication();

void main(int argc, char** argv) {
	ForLatte::Log::Init();

	FL_PROFILE_BEGIN_SESSION("Startup", "ForLatteProfile-Startup.json");
	auto app = ForLatte::CreateApplication();
	FL_PROFILE_END_SESSION();

	FL_PROFILE_BEGIN_SESSION("Runtime", "ForLatteProfile-Runtime.json");
	app->Run();
	FL_PROFILE_END_SESSION();

	FL_PROFILE_BEGIN_SESSION("Shutdown", "ForLatteProfile-Shutdown.json");
	delete app;
	FL_PROFILE_END_SESSION();
}

#endif