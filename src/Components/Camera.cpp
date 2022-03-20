#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"

Camera* Camera::mainCam = nullptr;

void Camera::SetOrtho(Camera& camera, const float windowWidth, const float windowHeight) {
	int ppuScale = 1;
	if (windowHeight >= 1700.0f) {
		ppuScale = 4;
	}
	else if (windowHeight >= 1300.0f) {
		ppuScale = 3;
	}
	else if (windowHeight >= 800.0f) {
		ppuScale = 2;
	}

	constexpr int pixelsPerUnit = 100;
	const float orthoSize = (windowHeight / (ppuScale * pixelsPerUnit)) * 0.5f;

	const float halfHeight = orthoSize; 
	const float aspectRatio = windowWidth / windowHeight;
	const float halfWidth = halfHeight * aspectRatio; 

	camera.projection = glm::ortho(-halfWidth, halfWidth, -halfHeight, halfHeight, 0.01f, 1000.0f);
	mainCam = &camera;
}
