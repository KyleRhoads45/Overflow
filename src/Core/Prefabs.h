#pragma once
#include <imgui/imgui.h>

struct IconData {
	ImTextureID textureId;
	ImVec2 uvMin = ImVec2(0.0f, 0.0f);
	ImVec2 uvMax = ImVec2(1.0f, 1.0f);
};

inline int prefabCount = 0;
const int playerPrefabId = 100;
const int sawPrefabId = 101;

void PrefabsInit();
void PlacePrefab(const int prefabId, const glm::vec3& pos);
void ErasePrefab(const glm::vec3& pos);
IconData GetPrefabIcon(const int prefabId);

