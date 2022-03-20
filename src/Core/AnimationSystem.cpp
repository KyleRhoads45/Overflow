#include "Scene.h"
#include "AnimationSystem.h"
#include <iostream>

void AnimationSystem::Update(const float deltaTime) {
	const auto& animView = GetView<Sprite, AnimationController>();

	for (auto entity : animView) {
		auto& sprite = animView.get<Sprite>(entity);
		auto& animController = animView.get<AnimationController>(entity);

		auto& animation = animController.animations[animController.state];
		animController.curTime += deltaTime;

		if (animController.state != animController.lastState) {
			animController.index = 0;
		}
		else if (animController.curTime < 1.0f / animation.fps) continue;
		else {
			if (++animController.index >= animation.centers.size()) {
				animController.index = 0;
			}
		}

		animController.curTime = 0.0f;
		animController.lastState = animController.state;

		sprite.textureId = animation.texture.id;
		sprite.SubTexture(animation.texture, animation.centers[animController.index], animation.cellWidth, animation.cellHeight);
	}

}
