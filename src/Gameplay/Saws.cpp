#include "../Core/Scene.h"
#include "../Components/Components.h"
#include "../Core/Prefabs.h"
#include "Saws.h"
#include "PlayerController.h"

static float curTime = 0.0f;

void SawsUpdate(const float deltaTime) {
	bool updateRotation = false;
	curTime += deltaTime;
	if (curTime >= 0.04f) {
		curTime = 0.0f;
		updateRotation = true;
	}

	const auto& sawView = GetComponentView<Transform, TriggerCircle, PrefabId>();
	for (const auto& entity : sawView) {
		if (GetComponent<PrefabId>(entity).id != SawPrefabId) continue;

		auto& trans = GetComponent<Transform>(entity);
		auto& trigger = GetComponent<TriggerCircle>(entity);

		if (updateRotation) {
			trans.rotation -= 45.0f;
		}

		if (trigger.triggered) {
			trigger.triggered = false;
			OnSawTrigger();
		}
	}
}
