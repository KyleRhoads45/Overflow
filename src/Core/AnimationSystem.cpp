#include "Scene.h"
#include "AnimationSystem.h"
#include "../Components/Components.h"
#include <iostream>

Animation::Animation(const Texture& texture, float fps, int cellWidth, int cellHeight, int count, int startOffset, bool loop)
: texture(texture), fps(fps), cellWidth(cellWidth), cellHeight(cellHeight), loop(loop) {

	const int rowCount = texture.height / cellHeight;
	const int colCount = texture.width / cellWidth;

	int curOffset = startOffset;
	for (int i = 0; i < count; i++) {
		int row = curOffset / colCount;
		int col = curOffset % colCount;

		int x = (cellWidth * col) + cellWidth / 2;
		int y = (texture.height - (cellHeight * row)) - cellHeight / 2;

		centers.push_back(glm::vec2(x, y));
		curOffset++;
	}
}

void AnimationUpdate(const float deltaTime) {
	const auto& animView = GetComponentView<Sprite, AnimationController>();

	for (const auto entity : animView) {
		auto& sprite = animView.get<Sprite>(entity);
		auto& controller = animView.get<AnimationController>(entity);
		auto& animation = controller.animations[controller.state];

		controller.curFrameTime += deltaTime;

		if (controller.state != controller.lastState) {
			controller.spriteIndex = 0;
			controller.curFrameTime = 0.0f;
			controller.lastState = controller.state;

			sprite.textureId = animation.texture.id;
			sprite.SubTexture(animation.texture, animation.centers[controller.spriteIndex], animation.cellWidth, animation.cellHeight);
		}

		const int maxAnimationSpriteIndex = animation.centers.size() - 1;

		if (!animation.loop && controller.spriteIndex >= maxAnimationSpriteIndex) continue;
		if (controller.curFrameTime < 1.0f / animation.fps) continue;

		controller.spriteIndex++;
		if (animation.loop && controller.spriteIndex >= maxAnimationSpriteIndex) {
			controller.spriteIndex = 0;
		}

		controller.curFrameTime = 0.0f;
		sprite.textureId = animation.texture.id;
		sprite.SubTexture(animation.texture, animation.centers[controller.spriteIndex], animation.cellWidth, animation.cellHeight);
	}

}
