#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"

Camera* Camera::mainCam = nullptr;

void Camera::SetOrtho(Camera& camera, const int windowWidth, const int windowHeight) {
	int ppuScale = 1;
	if (windowHeight >= 1700) {
		ppuScale = 4;
	}
	else if (windowHeight >= 1300) {
		ppuScale = 3;
	}
	else if (windowHeight >= 800) {
		ppuScale = 2;
	}

	constexpr int pixelsPerUnit = 100;
	const float orthoSize = ((float)windowHeight / (ppuScale * pixelsPerUnit)) * 0.5f;

	const float halfHeight = orthoSize; 
	const float aspectRatio = (float)windowWidth / (float)windowHeight;
	const float halfWidth = halfHeight * aspectRatio; 

	camera.projection = glm::ortho(-halfWidth, halfWidth, -halfHeight, halfHeight, 0.01f, 1000.0f);
	mainCam = &camera;
}
