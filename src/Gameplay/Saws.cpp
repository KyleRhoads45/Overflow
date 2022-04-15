#include "../Core/Scene.h"
#include "../Components/Components.h"
#include "Saws.h"
#include "PlayerController.h"
#include <iostream>

/*
void SawsStart() {
    for (int i = 0; i < 4; i++) {
        entt::entity sawEntity = CreateEntity(positions[i]);
		sawEntities[i] = sawEntity;

		TriggerCircle& triggerCircle = AddComponent<TriggerCircle>(sawEntity);
		triggerCircle.radius = 0.28f;

		Sprite& sprite = AddComponent<Sprite>(sawEntity);
		sprite.SetTexture(Texture::GetTexture("src/Assets/Sprites/Saws.png"));

		AnimationController& animController = AddComponent<AnimationController>(sawEntity);
		Animation rotate(Texture::GetTexture("src/Assets/Sprites/Saws.png"), 15.0f, 64, 64, 7, 1);
		animController.animations.push_back(rotate);
    }
}
*/

void SawsUpdate(const float deltaTime) {
	const auto& sawView = GetView<TriggerCircle>();
	for (const auto& entity : sawView) {
		TriggerCircle& trigger = GetComponent<TriggerCircle>(entity);
		if (trigger.triggered) {
			trigger.triggered = false;
			OnSawTrigger();
		}
	}
}
