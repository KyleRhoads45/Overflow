#pragma once
#include <glfw/glfw3.h>
#include "../Components/Components.h"

#define REGISTER_UPDATE \
	void Update(float); \
	bool result { Application::AddScript(*Update) };

class Application {

public:

	Application();
	static bool AddScript(void (*updatePtr)(float));

private:

	void Update();
	void Exit();

	const float GetDeltaTime();
	static void OnWindowResize(GLFWwindow* window, int width, int height);

	GLFWwindow* window;

};
