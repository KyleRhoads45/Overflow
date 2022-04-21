#pragma once

struct StaticBox {

	float width;
	float height;
	glm::vec2 offset;

	void Init(float width, float height, glm::vec2 offset) {
		this->width = width;
		this->height = height;
		this->offset = offset;
	};

};
