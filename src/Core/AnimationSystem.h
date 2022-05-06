#pragma once
#include <vector>
#include "glm/vec2.hpp"
#include "../Renderer/Texture.h"

struct Animation {

	Texture texture;
	std::vector<glm::vec2> centers;

	float cellWidth;
	float cellHeight;
	float fps;
	bool loop;

	Animation() = delete;
	Animation(const Texture& texture, float fps, int cellWidth, int cellHeight, int count, int startOffset, bool loop);

};

void AnimationUpdate(const float deltaTime);
