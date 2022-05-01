#pragma once
#include <imgui/imgui.h>
#include <glm/glm.hpp>

struct IconData {
	ImTextureID textureId;
	ImVec2 uvMin = ImVec2(0.0f, 0.0f);
	ImVec2 uvMax = ImVec2(1.0f, 1.0f);
};

inline int prefabCount = 0;
constexpr int PlayerPrefabId = 100;
constexpr int SawPrefabId = 101;
constexpr int BgPrefabId = 102;
constexpr int FlagPrefabId = 103;

void PrefabsInit();
void PlacePrefab(const int prefabId, glm::vec3 pos);
void ErasePrefab(const glm::vec3& pos);
IconData GetPrefabIcon(const int prefabId);

