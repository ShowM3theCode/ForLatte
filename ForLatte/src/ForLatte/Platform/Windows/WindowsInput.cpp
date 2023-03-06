#include "flpch.h"
#include "WindowsInput.h"

#include <GLFW/glfw3.h>
#include "ForLatte/Application.h"

namespace ForLatte {

	Input* Input::s_Instance = new WindowsInput();

	bool WindowsInput::IsKeyPressedImpl(int keycode) {
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::IsMouseButtonPressedImpl(int button) {
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	float WindowsInput::GetMouseXImpl() {
		auto [xPos, _] = GetMousePostion();
		return xPos;
	}

	float WindowsInput::GetMouseYImpl() {
		auto [_, yPos] = GetMousePostion();
		return yPos;
	}

	std::pair<float, float> WindowsInput::GetMousePostionImpl() {
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);
		return { (float)xPos, (float)yPos };
	}

}