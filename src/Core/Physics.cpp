#include <entt/entt.hpp>
#include "Math.h"
#include "Scene.h"
#include "Physics.h"
#include <iostream>

static void PerformAABB(Transform& trans, DynamicBox& boxShape);
static bool PerformCircleTrigger(Transform& trans, DynamicCircle& circle);

void PhysicsUpdate() {
	const auto& dynamicBoxView = GetView<Transform, DynamicBox>();
	for (auto entity : dynamicBoxView) {
		auto& trans = dynamicBoxView.get<Transform>(entity);
		auto& dynamicBox = dynamicBoxView.get<DynamicBox>(entity);

		dynamicBox.lastCenter = dynamicBox.center;
		dynamicBox.center = trans.position;

		const glm::vec3 lastCenter = dynamicBox.lastCenter;
		const glm::vec3 curCenter = dynamicBox.center;

		dynamicBox.rightColliding = false;
		dynamicBox.leftColliding = false;
		dynamicBox.upColliding = false;
		dynamicBox.downColliding = false;

		int sweepIterations = 50;
		for (int i = 0; i <= sweepIterations; i++) {
			float t = (float)i / (float)sweepIterations;
			dynamicBox.center = Vec3Lerp(lastCenter, curCenter, t);
			PerformAABB(trans, dynamicBox);
		}

		dynamicBox.center = trans.position;
	}

	const auto& dynamicCircleView = GetView<Transform, DynamicCircle>();
	for (auto entity : dynamicCircleView) {
		auto& trans = dynamicBoxView.get<Transform>(entity);
		auto& dynamicCircle = dynamicCircleView.get<DynamicCircle>(entity);

		dynamicCircle.lastCenter = dynamicCircle.center;
		dynamicCircle.center = trans.position;

		const glm::vec3 lastCenter = dynamicCircle.lastCenter;
		const glm::vec3 curCenter = dynamicCircle.center;

		int sweepIterations = 50;
		for (int i = 0; i <= sweepIterations; i++) {
			float t = (float)i / (float)sweepIterations;
			dynamicCircle.center = Vec3Lerp(lastCenter, curCenter, t);
			if (PerformCircleTrigger(trans, dynamicCircle)) {
				break;
			}
		}

		dynamicCircle.center = trans.position;
	}
}

void PerformAABB(Transform& trans, DynamicBox& dynamicBox) {
	const auto& otheBoxShapes = GetView<Transform, StaticBox>();
	for (auto& otherEntity : otheBoxShapes) {
		auto& otherTrans = otheBoxShapes.get<Transform>(otherEntity);
		auto& otherBox = otheBoxShapes.get<StaticBox>(otherEntity);

		glm::vec2 dynamicBoxBottomLeft = glm::vec2(dynamicBox.center.x - (dynamicBox.width / 2), dynamicBox.center.y - (dynamicBox.height / 2));
		glm::vec2 dynamicBoxTopRight = glm::vec2(dynamicBox.center.x + (dynamicBox.width / 2), dynamicBox.center.y + (dynamicBox.height / 2));

		glm::vec3 otherBoxPos(otherTrans.position.x + otherBox.offset.x, otherTrans.position.y + otherBox.offset.y, otherTrans.position.z);
		glm::vec2 otherBoxBottomLeft = glm::vec2(otherBoxPos.x - (otherBox.width / 2), otherBoxPos.y - (otherBox.height / 2));
		glm::vec2 otherBoxTopRight = glm::vec2(otherBoxPos.x + (otherBox.width / 2), otherBoxPos.y + (otherBox.height / 2));

		bool above = dynamicBoxBottomLeft.y > otherBoxTopRight.y;
		bool below = dynamicBoxTopRight.y < otherBoxBottomLeft.y;
		bool right = dynamicBoxBottomLeft.x > otherBoxTopRight.x;
		bool left = dynamicBoxTopRight.x < otherBoxBottomLeft.x;

		if (!above && !below && !right && !left) {
			const float reconcileOffset = 0.0001f;

			glm::vec2 lastBoxBottomLeft = glm::vec2(dynamicBox.lastCenter.x - (dynamicBox.width / 2), dynamicBox.lastCenter.y - (dynamicBox.height / 2));
			glm::vec2 lastBoxTopRight = glm::vec2(dynamicBox.lastCenter.x + (dynamicBox.width / 2), dynamicBox.lastCenter.y + (dynamicBox.height / 2));

			if (dynamicBoxBottomLeft.y <= otherBoxTopRight.y && lastBoxBottomLeft.y > otherBoxTopRight.y) {
				trans.position.y = otherBoxTopRight.y + (dynamicBox.height / 2.0f) + reconcileOffset;
				dynamicBox.downColliding = true;
			}
			else if (dynamicBoxTopRight.x >= otherBoxBottomLeft.x && lastBoxTopRight.x < otherBoxBottomLeft.x) {
				trans.position.x = otherBoxBottomLeft.x - (dynamicBox.width / 2.0f) - reconcileOffset;
				dynamicBox.rightColliding = true;
			}
			else if (dynamicBoxBottomLeft.x <= otherBoxTopRight.x && lastBoxBottomLeft.x > otherBoxTopRight.x) {
				trans.position.x = otherBoxTopRight.x + (dynamicBox.width / 2.0f) + reconcileOffset;
				dynamicBox.leftColliding = true;
			}
			else if (dynamicBoxTopRight.y >= otherBoxBottomLeft.y && lastBoxTopRight.y < otherBoxBottomLeft.y) {
				trans.position.y = otherBoxBottomLeft.y - (dynamicBox.height / 2.0f) - reconcileOffset;
				dynamicBox.upColliding = true;
			}

			dynamicBox.center = trans.position;
		}
	}
}

bool PerformCircleTrigger(Transform& trans, DynamicCircle& circle) {
	const auto& triggers = GetView<Transform, TriggerCircle>();
	for (auto& otherEntity : triggers) {
		auto& otherTrans = triggers.get<Transform>(otherEntity);
		auto& otherCircle = triggers.get<TriggerCircle>(otherEntity);

		float minTouchingDist = circle.radius + otherCircle.radius;
		float distFromCenters = Vec3Distance(trans.position, otherTrans.position);
		if (distFromCenters < minTouchingDist) {
			otherCircle.triggered = true;
			return true;
		}
		otherCircle.triggered = false;
	}
	return false;
}
