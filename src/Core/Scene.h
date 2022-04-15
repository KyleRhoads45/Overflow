#pragma once
#include <glm/glm.hpp>
#include <entt/entt.hpp>

struct Scene {
	entt::registry registry;
	std::string name;
};

inline Scene activeScene;

entt::entity CreateEntity();
entt::entity CreateEntity(const glm::vec3& pos);
void CreateScene(const std::string& sceneName);
void SaveScene();
void LoadScene(const std::string& sceneName);

template<typename Component>
Component& AddComponent(const entt::entity& entity) {
	return activeScene.registry.emplace<Component>(entity);
}

template<typename Component>
Component& GetComponent(const entt::entity& entity) {
	return activeScene.registry.get<Component>(entity);
}

template<typename ...Component>
auto GetView() {
	return activeScene.registry.view<Component...>();
}

