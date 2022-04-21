#include <vector>
#include <entt/entt.hpp>
#include "Scene.h"
#include "../Components/Components.h"
#include "Prefabs.h"
#include <iostream>

static std::vector<glm::vec2> tileSet1Centers;
static std::vector<glm::vec2> tileSet2Centers;

static std::array<int, 5> supportBeamIds = { 25, 28, 31, 34, 37 };
static std::array<int, 3> shortLeftPlatforms = { 26, 32, 35 };
static std::array<int, 3> shortRightPlatforms = { 27, 29, 33 };

static std::vector<glm::vec2> GenerateCenters(Texture& texture, int cellSize);
static void CreateStandardTile(const int prefabId, const entt::entity entity);
static Texture GetTextureFromPrefabId(const int prefabId);
static glm::vec2 GetCenterFromPrefabId(const int prefabId);
static bool ArrayContains(int* arry, int size, int prefabId);

void PrefabsInit() {
	Texture texSet1 = Texture::GetTexture("src/Assets/Sprites/1_Industrial_Tileset_1.png");
	Texture texSet2 = Texture::GetTexture("src/Assets/Sprites/1_Industrial_Tileset_3.png");

	tileSet1Centers = GenerateCenters(texSet1, 32);
	tileSet2Centers = GenerateCenters(texSet2, 32);

	prefabCount = tileSet1Centers.size() + tileSet2Centers.size();
}


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

	Texture texture = GetTextureFromPrefabId(prefabId);
	glm::vec2 center = GetCenterFromPrefabId(prefabId);

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

static std::vector<glm::vec2> GenerateCenters(Texture& texture, int cellSize) {
	const int rowCount = texture.height / cellSize;
	const int colCount = texture.width / cellSize;
	const int cellCount = rowCount * colCount;
	
	std::vector<glm::vec2> centers;
	for (int i = 0; i < cellCount; i++) {
		int row = i / colCount;
		int col = i % colCount;

		int x = (cellSize * col) + cellSize / 2;
		int y = (texture.height - (cellSize * row)) - cellSize / 2;

		centers.push_back(glm::vec2(x, y));
	}

	return centers;
}

static void CreateStandardTile(const int prefabId, const entt::entity entity) {
	AddComponent<PrefabId>(entity).id = prefabId;

	bool isSupportBeam = ArrayContains(&supportBeamIds[0], supportBeamIds.size(), prefabId);
	bool isShortLeftPlatform = ArrayContains(&shortLeftPlatforms[0], shortLeftPlatforms.size(), prefabId);
	bool isShortRightPlatform = ArrayContains(&shortRightPlatforms[0], shortRightPlatforms.size(), prefabId);

	if (isShortLeftPlatform) {
		AddComponent<StaticBox>(entity).Init(0.24f, 0.32f, glm::vec2(0.04f, 0.0f));
	}
	else if (isShortRightPlatform) {
		AddComponent<StaticBox>(entity).Init(0.24f, 0.32f, glm::vec2(-0.04f, 0.0f));
	}
	else if (!isSupportBeam) {
		AddComponent<StaticBox>(entity).Init(0.32f, 0.32f, glm::vec2(0.0f, 0.0f));
	}

	Sprite& sr = AddComponent<Sprite>(entity);

	Texture tileTexture = GetTextureFromPrefabId(prefabId);
	sr.SetTexture(tileTexture);
	sr.SubTexture(tileTexture, GetCenterFromPrefabId(prefabId), 32, 32);
}

static Texture GetTextureFromPrefabId(const int prefabId) {
	if (prefabId < tileSet1Centers.size()) {
		return Texture::GetTexture("src/Assets/Sprites/1_Industrial_Tileset_1.png");
	}
	return Texture::GetTexture("src/Assets/Sprites/1_Industrial_Tileset_3.png");
}

static glm::vec2 GetCenterFromPrefabId(const int prefabId) {
	if (prefabId < tileSet1Centers.size()) {
		return tileSet1Centers[prefabId];
	}
	return tileSet2Centers[prefabId - tileSet1Centers.size()];
}

static bool ArrayContains(int* arry, int size, int prefabId) {
	for (int i = 0; i < size; i++) {
		if (arry[i] == prefabId) return true;
	}
	return false;
}
