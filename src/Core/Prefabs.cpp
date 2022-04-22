#include <iostream>
#include <vector>
#include <entt/entt.hpp>
#include "Scene.h"
#include "../Components/Components.h"
#include "Prefabs.h"

static std::vector<glm::vec2> tileSet1Centers;
static std::vector<glm::vec2> tileSet2Centers;

static std::array<int, 5> supportBeamIds = { 25, 28, 31, 34, 37 };
static std::array<int, 3> shortLeftPlatforms = { 26, 32, 35 };
static std::array<int, 3> shortRightPlatforms = { 27, 29, 33 };

static void PlacePlayer(const glm::vec3& pos);
static void PlaceSaw(const glm::vec3& pos);
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
	if (prefabId == playerPrefabId) {
		PlacePlayer(glm::vec3(pos.x, pos.y, 1.0f));
		return;
	}

	if (prefabId == sawPrefabId) {
		PlaceSaw(glm::vec3(pos.x, pos.y, -1.0f));
		return;
	}

	entt::entity entity = CreateEntity(pos);
	ErasePrefab(pos);
	CreateStandardTile(prefabId, entity);
}

void ErasePrefab(const glm::vec3& pos) {
	const auto& serializeView = GetView<Transform, PrefabId>();
	for (const auto& [entity, trans, prefabId] : serializeView.each()) {
		if (trans.position == pos) {
			activeScene.registry.destroy(entity);
			break;
		}
	}
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

static void PlacePlayer(const glm::vec3& pos) {
	const auto& playerView = GetView<DynamicBox>();
	if (playerView.size() != 0) {
		auto& trans = GetComponent<Transform>(playerView[0]);
		trans.position = pos;
		return;
	}

	entt::entity playerEntity = CreateEntity(pos);
	AddComponent<PrefabId>(playerEntity).id = playerPrefabId;

    auto& trans = GetComponent<Transform>(playerEntity);

    auto& dynamicBox = AddComponent<DynamicBox>(playerEntity);
    dynamicBox.Init(0.15f, 0.3f, trans.position);

    auto& dynamicCircle = AddComponent<DynamicCircle>(playerEntity);
    dynamicCircle.radius = 0.12f;
    
    auto& sprite = AddComponent<Sprite>(playerEntity);
    sprite.SetTexture(Texture::GetTexture("src/Assets/Sprites/PlayerIdle.png"));
    sprite.SubTexture(Texture::GetTexture("src/Assets/Sprites/PlayerIdle.png"), glm::vec2(16, 80), 32, 32);

    auto& animController = AddComponent<AnimationController>(playerEntity);
    Animation idleAnim(Texture::GetTexture("src/Assets/Sprites/PlayerIdle.png"), 10.0f, 32, 32, 9, 0);
    animController.animations.push_back(idleAnim);

    Animation runAnim(Texture::GetTexture("src/Assets/Sprites/PlayerRun.png"), 20.0f, 32, 32, 6, 0);
    animController.animations.push_back(runAnim);

    Animation jumpAnim(Texture::GetTexture("src/Assets/Sprites/PlayerJump.png"), 10.0f, 32, 32, 4, 1);
    animController.animations.push_back(jumpAnim);

    Animation fallAnim(Texture::GetTexture("src/Assets/Sprites/PlayerJump.png"), 10.0f, 32, 32, 1, 5);
    animController.animations.push_back(fallAnim);
}

static void PlaceSaw(const glm::vec3& pos) {
	ErasePrefab(pos);

	entt::entity sawEntity = CreateEntity(pos);
	AddComponent<PrefabId>(sawEntity).id = sawPrefabId;

	TriggerCircle& triggerCircle = AddComponent<TriggerCircle>(sawEntity);
	triggerCircle.radius = 0.28f;

	Sprite& sprite = AddComponent<Sprite>(sawEntity);
	sprite.SetTexture(Texture::GetTexture("src/Assets/Sprites/Saws.png"));
    sprite.SubTexture(Texture::GetTexture("src/Assets/Sprites/Saws.png"), glm::vec2(32, 32), 64, 64);

	AnimationController& animController = AddComponent<AnimationController>(sawEntity);
	Animation rotate(Texture::GetTexture("src/Assets/Sprites/Saws.png"), 15.0f, 64, 64, 7, 1);
	animController.animations.push_back(rotate);
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
	else if (isSupportBeam) {
		GetComponent<Transform>(entity).position.z = 2;
	}
	else {
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
