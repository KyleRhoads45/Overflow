#include <glm/gtc/matrix_transform.hpp>
#include "../Components/Components.h"
#include "CameraSystem.h"
#include <iostream>

void CameraSystem::Update(Scene& scene) {
	const auto& cameraView = scene.registry.view<Transform, Camera>();
	for (const auto entity : cameraView) {
		Transform& trans = cameraView.get<Transform>(entity);
		Camera& cam = cameraView.get<Camera>(entity);
		cam.view = glm::translate(glm::mat4(1.0f), -trans.position);
	}
}
