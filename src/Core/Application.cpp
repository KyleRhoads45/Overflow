#include <iostream>
#include <string>
#include <glad/glad.h>
#include "Input.h"
#include "Physics.h"
#include "AnimationSystem.h"
#include "CameraSystem.h"
#include "Prefabs.h"
#include "../Editor/Editor.h"
#include "../Renderer/Renderer.h"
#include "../Renderer/Texture.h"
#include "../Gameplay/PlayerController.h"
#include "../Gameplay/Saws.h"
#include "Application.h"

Application::Application() {
	if (!glfwInit()) {
		std::cout << "Failed to init glfw\n";
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	window = glfwCreateWindow(1920, 1080, "Overflow", NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(0);
	glfwSetWindowSizeCallback(window, OnWindowResize);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to load Opengl function pointers\n";
	}

	InputInit(window);
	RendererInit();
	PrefabsInit();
	EditorInit(window);

	const entt::entity camEntity = CreateEntity(glm::vec3(0, 0, 10));
	Camera& cam = AddComponent<Camera>(camEntity);
	Camera::SetOrtho(cam, 1920, 1080);

	//PlayerStart();
	
	while (true) {
		Update();
	}
}

void Application::Update() {
	glfwPollEvents();
	
	float deltaTime = GetDeltaTime();
	std::string windowTitle = "Overflow " + std::to_string((int)(1.0 / deltaTime)) + "fps";
	glfwSetWindowTitle(window, windowTitle.c_str());

	AnimationUpdate(deltaTime);
	//PlayerUpdate(deltaTime);
	SawsUpdate(deltaTime);
	PhysicsUpdate();
	CameraSystemUpdate();
	RendererRenderScene(activeScene);
	EditorUpdate(window);
	RendererEndFrame(window);
	
	if (glfwWindowShouldClose(window)) {
		Exit();
	}
}

void Application::Exit() {
	glfwTerminate();
	exit(0);
}

void Application::OnWindowResize(GLFWwindow* w, int width, int height) {
	glViewport(0, 0, width, height);
	Camera::SetOrtho(*Camera::mainCam, width, height);
}

const float Application::GetDeltaTime() {
	static float lastTime = 0;
    const float currentTime = glfwGetTime();
    const float deltaTime = currentTime - lastTime;
    lastTime = currentTime;
    return deltaTime;
}
