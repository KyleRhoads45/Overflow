#include <entt/entt.hpp>
#include "Scene.h"
#include "../Components/Components.h"
#include "Prefabs.h"

static glm::vec2 centers[] = {
	glm::vec2(16, 16),
	glm::vec2(48, 16),
	glm::vec2(80, 16),
	glm::vec2(112, 16),
	glm::vec2(144, 16),
	glm::vec2(176, 16),

	glm::vec2(16, 48),
	glm::vec2(48, 48),
	glm::vec2(80, 48),
	glm::vec2(112, 48),
	glm::vec2(144, 48),
	glm::vec2(176, 48),

	glm::vec2(16, 80),
	glm::vec2(48, 80),
	glm::vec2(80, 80),
	glm::vec2(112, 80),
	glm::vec2(144, 80),
	glm::vec2(176, 80),

	glm::vec2(16, 112),
	glm::vec2(48, 112),
	glm::vec2(80, 112),
	glm::vec2(112, 112),
	glm::vec2(144, 112),
	glm::vec2(176, 112)
};
	
static void CreateStandardTile(const int prefabId, const entt::entity entity);

void PlacePrefab(const int prefabId, const glm::vec3& pos) {
	entt::entity entity = CreateEntity(pos);

	const auto& serializeView = GetView<Transform, PrefabId>();
	for (const auto& [entity, trans, prefabId] : serializeView.each()) {
		if (trans.position == pos) {
			activeScene.registry.destroy(entity);
			break;
		}
	}
	
	CreateStandardTile(prefabId, entity);
}

IconData GetPrefabIcon(const int prefabId) {
	IconData data;

	Texture texture = Texture::GetTexture("src/Assets/Sprites/1_Industrial_Tileset_1.png");
	glm::vec2 center = centers[prefabId];

	const int cellWidth = 32;
	const int cellHeight = 32;
	const int pixelsPerUnit = 100;

	const float halfWidth = (cellWidth / 2.0f) / pixelsPerUnit;
	const float halfHeight = (cellHeight / 2.0f) / pixelsPerUnit;

	const float halfCellWidth = cellWidth / 2.0f;
	const float halfCellHeight = cellHeight / 2.0f;

	ImVec2 uvMin;
	ImVec2 uvMax;

	uvMin.x = (center.x - halfCellWidth) / texture.width;
	uvMin.y = (center.y + halfCellHeight) / texture.height;

	uvMax.x = (center.x + halfCellWidth) / texture.width;
	uvMax.y = (center.y - halfCellHeight) / texture.height;

	data.textureId = (ImTextureID)texture.id;
	data.uvMin = uvMin;
	data.uvMax = uvMax;
	
	return data;
}

void CreateStandardTile(const int prefabId, const entt::entity entity) {
	AddComponent<PrefabId>(entity).id = prefabId;
	AddComponent<StaticBox>(entity).Init(0.32f, 0.32f);
	Texture tileTexture = Texture::GetTexture("src/Assets/Sprites/1_Industrial_Tileset_1.png");
	Sprite& sr = AddComponent<Sprite>(entity);
	sr.SetTexture(tileTexture);
	sr.SubTexture(tileTexture, centers[prefabId], 32, 32);
}
