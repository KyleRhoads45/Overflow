#pragma once
#include <glfw/glfw3.h>
#include "../Components/Components.h"

class Application {

public:

	Application();

private:

	void Update();
	void Exit();

	const float GetDeltaTime();
	static void OnWindowResize(GLFWwindow* window, int width, int height);

	GLFWwindow* window;

};
