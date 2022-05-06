#pragma once
#include <glm/glm.hpp>

struct TriggerCircle {
	float radius;
	glm::vec2 center;
	bool triggered;

	void Init(const float radius, const glm::vec2& center) {
		this->radius = radius;
		this->center = center;
		triggered = false;
	}
};
