#include "../Core/Scene.h"
#include "../Components/Components.h"
#include "Saws.h"
#include "PlayerController.h"
#include <iostream>

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
