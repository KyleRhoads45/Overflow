#include "../Components/Components.h"
#include "Scene.h"

entt::entity CreateEntity() {
	const entt::entity newEntity = activeScene->registry.create();
	Transform& trans = activeScene->registry.emplace<Transform>(newEntity);
	trans.position = glm::vec3(0.0f, 0.0f, 0.0f);
	trans.scale = glm::vec3(1.0f, 1.0f, 1.0f);
	trans.rotation = 0.0f;
	return newEntity;
}

entt::entity CreateEntity(const glm::vec3& pos) {
	const entt::entity newEntity = activeScene->registry.create();
	Transform& trans = activeScene->registry.emplace<Transform>(newEntity);
	trans.position = pos;
	trans.scale = glm::vec3(1.0f, 1.0f, 1.0f);
	trans.rotation = 0.0f;
	return newEntity;
}

void SceneCreateAndBind() {
	activeScene = std::make_unique<Scene>();	
}
