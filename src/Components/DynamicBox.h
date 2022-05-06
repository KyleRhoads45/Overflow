#pragma once
#include <glm/glm.hpp>

struct DynamicBox {
	float width;
	float height;

	glm::vec3 center;
	glm::vec3 lastCenter;

	bool rightColliding;
	bool leftColliding;
	bool upColliding;
	bool downColliding;

	void Init(const float width, const float height, const glm::vec3& center) {
		this->width = width;
		this->height = height;
		this->center = center;
		lastCenter = center;

		rightColliding = false;
		leftColliding = false;
		upColliding = false;
		downColliding = false;
	}
};
