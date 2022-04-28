#pragma once
#include <glm/glm.hpp>

struct Camera {
	glm::mat4 view;
	glm::mat4 projection;

	static Camera* mainCam;
	static void SetOrtho(Camera& camera, const int windowWidth, const int windowHeight);
};

