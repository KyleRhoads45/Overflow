#pragma once
#include <glm/glm.hpp>

struct DynamicCircle {
	float radius;
	glm::vec3 center;
	glm::vec3 lastCenter;

	void Init(const float radius, const glm::vec3& center) {
		this->radius = radius;
		this->center = center;
		lastCenter = center;
	}
};
