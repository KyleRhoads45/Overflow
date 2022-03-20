#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "../Renderer/Texture.h"

struct Animation {

	Texture texture;
	std::vector<glm::vec2> centers;

	float cellWidth;
	float cellHeight;
	float fps;

	Animation() = delete;
	Animation(const Texture& texture, float fps, int cellWidth, int cellHeight, int count, int startOffset);
};

struct AnimationController {

	int state = 0;
	int lastState = 0;
	int index = 0;
	float curTime = 0;
	std::vector<Animation> animations;

};
