#include "../Core/Prefabs.h"
#include "../Core/Scene.h"
#include "../Components/Components.h"
#include "Flag.h"

static int curScene = 0;
static std::string scenes[] {
	"Level01",
	"Level02",
	"Level03",
};

void FlagUpdate() {
	for (auto [entity, triggerCircle, prefabId] : GetEachComponent<TriggerCircle, PrefabId>()) {
		if (prefabId.id != FlagPrefabId) continue;

		if (triggerCircle.triggered) {
			triggerCircle.triggered = false;
			curScene++;
			if (curScene >= 3) {
				curScene = 0;
			}
			LoadScene(scenes[curScene]);
		}
	}
}

void FlagSetSceneIndex(int sceneIndex) {
	curScene = sceneIndex;
}
