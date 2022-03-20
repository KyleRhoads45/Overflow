#pragma once
#include <glm/glm.hpp>

struct DynamicBox {

	float width;
	float height;

	glm::vec3 center;
	glm::vec3 lastCenter;

	bool rightColliding = false;
	bool leftColliding = false;
	bool upColliding = false;
	bool downColliding = false;

	void Init(float width, float height, glm::vec3& pos) {
		this->width = width;
		this->height = height;
		center = pos;
		lastCenter = pos;
	};

};
