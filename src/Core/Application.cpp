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
#include "../Gameplay/PlayerController.h"
#include "../Gameplay/Saws.h"
#include "../Gameplay/Flag.h"
#include "../Components/Components.h"
#include "Application.h"
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

static void Update();
static void Exit();
static float GetDeltaTime();
static void OnWindowResize(GLFWwindow* window, int width, int height);

static GLFWwindow* window;

void AppRun() {
	if (!glfwInit()) {
		std::cout << "Failed to init glfw\n";
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	window = glfwCreateWindow(1920, 1080, "Super Alright Game", NULL, NULL);
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

	LoadScene("Level01");

	const entt::entity camEntity = CreateEntity(glm::vec3(0, 0, 10));
	Camera& cam = AddComponent<Camera>(camEntity);
	Camera::SetOrtho(cam, 1920, 1080);

	while (true) {
		Update();
	}
}

static void Update() {
	glfwPollEvents();

	const float deltaTime = GetDeltaTime();

	//Ignore really long frames
	if (deltaTime >= 0.1f) return;

	const std::string windowTitle = "Overflow " + std::to_string((int)(1.0f / deltaTime)) + "fps";
	glfwSetWindowTitle(window, windowTitle.c_str());

	AnimationUpdate(deltaTime);
	PlayerUpdate(deltaTime);
	SawsUpdate(deltaTime);
	FlagUpdate();
	PhysicsUpdate(deltaTime);
	CameraSystemUpdate();
	RendererRenderScene(activeScene);
	EditorUpdate(window);
	RendererEndFrame(window);
	
	if (glfwWindowShouldClose(window)) {
		Exit();
	}
}

static void Exit() {
	glfwTerminate();
	exit(0);
}

static void OnWindowResize(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	Camera::SetOrtho(*Camera::mainCam, width, height);
}

static float GetDeltaTime() {
	static double lastTime = 0;
    const double currentTime = glfwGetTime();
	const float deltaTime = (float)(currentTime - lastTime);
    lastTime = currentTime;
    return deltaTime;
}
