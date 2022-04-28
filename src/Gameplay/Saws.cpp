#include "../Core/Scene.h"
#include "../Components/Components.h"
#include "Saws.h"
#include "PlayerController.h"

void SawsUpdate(const float deltaTime) {
	const auto& sawView = GetComponentView<TriggerCircle, AnimationController>();
	for (const auto& entity : sawView) {
		TriggerCircle& trigger = GetComponent<TriggerCircle>(entity);
		if (trigger.triggered) {
			trigger.triggered = false;
			OnSawTrigger();
		}
	}
}
