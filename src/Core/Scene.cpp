#include <fstream>
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
	activeScene = std::make_shared<Scene>();	
}

void SaveScene(std::shared_ptr<Scene> scene) {
	std::ofstream output;
	output.open("src/Assets/Scenes/TestScene", std::ios::out | std::ios::binary);

	char string[] = "Is this working";
	output.write("Is this working", sizeof(string));
}

void LoadScene() {

}
