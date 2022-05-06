#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "../Core/AnimationSystem.h"
#include "../Renderer/Texture.h"

struct AnimationController {
	int state = 0;
	int lastState = 0;
	int spriteIndex = 0;
	float curFrameTime = 0;
	std::vector<Animation> animations;
};
