#include "../Components/Components.h"
#include "../Renderer/Renderer.h"
#include "../Core/Scene.h"
#include "../Core/Input.h"
#include "Editor.h"

bool Editor::showGizmos = false;

void Editor::Update() {
	if (OnKeyHold(GLFW_KEY_G)) {
		showGizmos = true;
	}

	if (OnKeyHold(GLFW_KEY_H)) {
		showGizmos = false;
	}

	if (!showGizmos) return;

	RenderAllGizmos();
}

void Editor::RenderAllGizmos() {
	const auto& dynamicBoxView = activeScene->registry.view<Transform, DynamicBox>();
	for (const auto& [entity, trans, box] : dynamicBoxView.each()) {
		Renderer::DebugDrawRect(trans.position, box.width, box.height);
	}

	const auto& staticBoxView = activeScene->registry.view<Transform, StaticBox>();
	for (const auto& [entity, trans, box] : staticBoxView.each()) {
		Renderer::DebugDrawRect(trans.position, box.width, box.height);
	}

	const auto& dynamicCircleView = activeScene->registry.view<Transform, DynamicCircle>();
	for (const auto& [entity, trans, circle] : dynamicCircleView.each()) {
		Renderer::DebugDrawCircle(trans.position, circle.radius);
	}

	const auto& triggerCircleView = activeScene->registry.view<Transform, TriggerCircle>();
	for (const auto& [entity, trans, circle] : triggerCircleView.each()) {
		Renderer::DebugDrawCircle(trans.position, circle.radius);
	}
}
