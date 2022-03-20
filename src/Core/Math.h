#pragma once
#include <glm/glm.hpp>
#include <limits>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#define vec3Right glm::vec3(1.0f, 0.0f, 0.0f)
#define vec3Left glm::vec3(-1.0f, 0.0f, 0.0f)
#define vec3Up glm::vec3(0.0f, 1.0f, 0.0f)
#define vec3Down glm::vec3(0.0f, -1.0f, 0.0f)
#define vec3Forward glm::vec3(0.0f, 0.0f, 1.0f)
#define vec3Backward glm::vec3(0.0f, 0.0f, -1.0f)

glm::vec3 Vec3Lerp(const glm::vec3& a, const glm::vec3& b, float t);
float Vec3Distance(const glm::vec3& a, const glm::vec3& b);
float MoveTowardsZero(const float val, const float step);

