#include <fstream>
#include "../Components/Components.h"
#include "Scene.h"
#include "Prefabs.h"
#include <iostream>

entt::entity CreateEntity() {
	const entt::entity newEntity = activeScene.registry.create();
	Transform& trans = activeScene.registry.emplace<Transform>(newEntity);
	trans.position = glm::vec3(0.0f, 0.0f, 0.0f);
	trans.scale = glm::vec3(1.0f, 1.0f, 1.0f);
	trans.rotation = 0.0f;
	return newEntity;
}

entt::entity CreateEntity(const glm::vec3& pos) {
	const entt::entity newEntity = activeScene.registry.create();
	Transform& trans = activeScene.registry.emplace<Transform>(newEntity);
	trans.position = pos;
	trans.scale = glm::vec3(1.0f, 1.0f, 1.0f);
	trans.rotation = 0.0f;
	return newEntity;
}

void CreateScene(const std::string& sceneName) {
	activeScene.registry.clear();
	activeScene.name = sceneName;
}

void SaveScene() {
	const std::string scenePath = "src/Assets/Scenes/" + activeScene.name;
	std::ofstream output(scenePath);

	const auto& serializeView = GetView<Transform, PrefabId>();
	for (const auto& [entity, trans, prefabId] : serializeView.each()) {
		output << prefabId.id << ' ' << trans.position.x << ' ' << trans.position.y << ' ' << trans.position.z << "\n";
	}

	output.close();
}

void LoadScene(const std::string& sceneName) {
	CreateScene(sceneName);

	const std::string scenePath = "src/Assets/Scenes/" + sceneName;
	std::ifstream input(scenePath);

	while (input.good()) {
		glm::vec3 pos;
		unsigned int prefabId;
		input >> prefabId >> pos.x >> pos.y >> pos.z;
		PlacePrefab(prefabId, pos);
	}

	input.close();
}
