#include "Math.h"

glm::vec3 Vec3Lerp(const glm::vec3& a, const glm::vec3& b, const float t) {
	float tClamped = glm::clamp(t, 0.0f, 1.0f);
	return glm::vec3(a.x + (b.x - a.x) * tClamped, a.y + (b.y - a.y) * tClamped, a.z + (b.z - a.z) * tClamped);
}

float Vec2Distance(const glm::vec3& a, const glm::vec3& b) {
	return glm::sqrt(glm::pow(b.x - a.x, 2) + glm::pow(b.y - a.y, 2));
}

float Vec3Distance(const glm::vec3& a, const glm::vec3& b) {
	return glm::sqrt(glm::pow(b.x - a.x, 2) + glm::pow(b.y - a.y, 2) + glm::pow(b.z - a.z, 2));
}

float MoveTowardsZero(const float val, const float step) {
	if (val == 0.0f) {
		return 0.0f;
	}
	if (val > 0.0f) {
		return glm::clamp(val - step, 0.0f, INFINITY);
	}
	return glm::clamp(val + step, -INFINITY, 0.0f);
}
