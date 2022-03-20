#include "../Core/Scene.h"
#include "../Components/Components.h"
#include "Saws.h"
#include "PlayerController.h"
#include <iostream>

static entt::entity sawEntities[4];
static glm::vec3 positions[] {
	glm::vec3(0.8f, -1.9f, -1.0f),
	glm::vec3(1.2f, -0.32f, -1.0f),
	glm::vec3(-1.0f, -0.4f, -1.0f),
	glm::vec3(-2.0f, 0.5f, -1.0f)
};

void Saws::Start() {
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

void Saws::Update(const float deltaTime) {
	for (int i = 0; i < 4; i++) {
		TriggerCircle& trigger = GetComponent<TriggerCircle>(sawEntities[i]);
		if (trigger.triggered) {
			trigger.triggered = false;
			OnSawTrigger();
		}
	}
}
