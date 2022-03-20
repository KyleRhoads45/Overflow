#pragma once
#include <glm/glm.hpp>

struct Transform {

	glm::vec3 position;
	glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
	float rotation;

};

