#include "../Core/Scene.h"
#include "../Components/Components.h"
#include "Level.h"

void Level::Start() {
	const entt::entity bgEntity = CreateEntity(glm::vec3(0.0f, 0.0f, -10.0f));
	GetComponent<Transform>(bgEntity).scale = glm::vec3(1.5f, 1.5f, 1.5f);
	Sprite& bgsr = AddComponent<Sprite>(bgEntity);

	Texture tex = Texture::GetTexture("src/Assets/Sprites/FarBG.png");
	bgsr.SetTexture(tex);

	entt::entity tileEntity = CreateEntity(glm::vec3(0.0f, 0.0f, 0.0f));
	AddComponent<StaticBox>(tileEntity).Init(0.32f, 0.32f);
	Sprite& sr = AddComponent<Sprite>(tileEntity);
	Texture tileTexture = Texture::GetTexture("src/Assets/Sprites/1_Industrial_Tileset_1.png");
	sr.SubTexture(tileTexture, glm::vec2(144, 80), 32, 32);

	return;
	//Ground
	for (int i = 0; i < 25; i++) {
		entt::entity tileEntity = CreateEntity(glm::vec3(-3.9f + (0.32 * i), -2.0f, 0.0f));

		AddComponent<StaticBox>(tileEntity).Init(0.32f, 0.32f);

		Sprite& sr = AddComponent<Sprite>(tileEntity);
		Texture tileTexture = Texture::GetTexture("src/Assets/Sprites/1_Industrial_Tileset_1.png");
		sr.SetTexture(tileTexture);
		if (i == 0) {
			sr.SubTexture(tileTexture, glm::vec2(144, 80), 32, 32);
		}
		else if (i == 24) {
			sr.SubTexture(tileTexture, glm::vec2(176, 80), 32, 32);
		}
		else {
			sr.SubTexture(tileTexture, glm::vec2(48, 80), 32, 32);
		}

	}

	for (int i = 0; i < 31; i++) {
		entt::entity tileEntity = CreateEntity(glm::vec3(-4.86f + (0.32 * i), -2.32f, 0.0f));

		AddComponent<StaticBox>(tileEntity).Init(0.32f, 0.32f);

		Sprite& sr = AddComponent<Sprite>(tileEntity);
		Texture tileTexture = Texture::GetTexture("src/Assets/Sprites/1_Industrial_Tileset_1.png");
		sr.SetTexture(tileTexture);
		sr.SubTexture(tileTexture, glm::vec2(48, 48), 32, 32);
	}

	for (int i = 0; i < 31; i++) {
		entt::entity tileEntity = CreateEntity(glm::vec3(-4.86f + (0.32 * i), -2.64f, 0.0f));

		AddComponent<StaticBox>(tileEntity).Init(0.32f, 0.32f);

		Sprite& sr = AddComponent<Sprite>(tileEntity);
		Texture tileTexture = Texture::GetTexture("src/Assets/Sprites/1_Industrial_Tileset_1.png");
		sr.SetTexture(tileTexture);
		sr.SubTexture(tileTexture, glm::vec2(48, 48), 32, 32);
	}

	//Walls

	for (int i = 0; i < 12; i++) {
		entt::entity tileEntity = CreateEntity(glm::vec3(3.78f, -1.68f + (i * 0.32), 0.0f));
		AddComponent<StaticBox>(tileEntity).Init(0.32f, 0.32f);
		Sprite& sr = AddComponent<Sprite>(tileEntity);
		Texture tileTexture = Texture::GetTexture("src/Assets/Sprites/1_Industrial_Tileset_1.png");
		sr.SetTexture(tileTexture);
		sr.SubTexture(tileTexture, glm::vec2(16, 48), 32, 32);
	}

	for (int i = 0; i < 12; i++) {
		entt::entity tileEntity = CreateEntity(glm::vec3(-3.9f, -1.68f + (i * 0.32), 0.0f));
		AddComponent<StaticBox>(tileEntity).Init(0.32f, 0.32f);
		Sprite& sr = AddComponent<Sprite>(tileEntity);
		Texture tileTexture = Texture::GetTexture("src/Assets/Sprites/1_Industrial_Tileset_1.png");
		sr.SetTexture(tileTexture);
		sr.SubTexture(tileTexture, glm::vec2(80, 48), 32, 32);
	}

	for (int i = 0; i < 14; i++) {
		entt::entity tileEntity = CreateEntity(glm::vec3(-4.22f, -2.0f + (i * 0.32), 0.0f));
		AddComponent<StaticBox>(tileEntity).Init(0.32f, 0.32f);
		Sprite& sr = AddComponent<Sprite>(tileEntity);
		Texture tileTexture = Texture::GetTexture("src/Assets/Sprites/1_Industrial_Tileset_1.png");
		sr.SetTexture(tileTexture);
		sr.SubTexture(tileTexture, glm::vec2(48, 48), 32, 32);
	}

	for (int i = 0; i < 14; i++) {
		entt::entity tileEntity = CreateEntity(glm::vec3(-4.54f, -2.0f + (i * 0.32), 0.0f));
		AddComponent<StaticBox>(tileEntity).Init(0.32f, 0.32f);
		Sprite& sr = AddComponent<Sprite>(tileEntity);
		Texture tileTexture = Texture::GetTexture("src/Assets/Sprites/1_Industrial_Tileset_1.png");
		sr.SetTexture(tileTexture);
		sr.SubTexture(tileTexture, glm::vec2(48, 48), 32, 32);
	}

	for (int i = 0; i < 14; i++) {
		entt::entity tileEntity = CreateEntity(glm::vec3(-4.86f, -2.0f + (i * 0.32), 0.0f));
		AddComponent<StaticBox>(tileEntity).Init(0.32f, 0.32f);
		Sprite& sr = AddComponent<Sprite>(tileEntity);
		Texture tileTexture = Texture::GetTexture("src/Assets/Sprites/1_Industrial_Tileset_1.png");
		sr.SetTexture(tileTexture);
		sr.SubTexture(tileTexture, glm::vec2(48, 48), 32, 32);
	}

	for (int i = 0; i < 14; i++) {
		entt::entity tileEntity = CreateEntity(glm::vec3(4.1f, -2.0f + (i * 0.32), 0.0f));
		AddComponent<StaticBox>(tileEntity).Init(0.32f, 0.32f);
		Sprite& sr = AddComponent<Sprite>(tileEntity);
		Texture tileTexture = Texture::GetTexture("src/Assets/Sprites/1_Industrial_Tileset_1.png");
		sr.SetTexture(tileTexture);
		sr.SubTexture(tileTexture, glm::vec2(48, 48), 32, 32);
	}

	for (int i = 0; i < 14; i++) {
		entt::entity tileEntity = CreateEntity(glm::vec3(4.42f, -2.0f + (i * 0.32), 0.0f));
		AddComponent<StaticBox>(tileEntity).Init(0.32f, 0.32f);
		Sprite& sr = AddComponent<Sprite>(tileEntity);
		Texture tileTexture = Texture::GetTexture("src/Assets/Sprites/1_Industrial_Tileset_1.png");
		sr.SetTexture(tileTexture);
		sr.SubTexture(tileTexture, glm::vec2(48, 48), 32, 32);
	}

	for (int i = 0; i < 14; i++) {
		entt::entity tileEntity = CreateEntity(glm::vec3(4.74f, -2.0f + (i * 0.32), 0.0f));
		AddComponent<StaticBox>(tileEntity).Init(0.32f, 0.32f);
		Sprite& sr = AddComponent<Sprite>(tileEntity);
		Texture tileTexture = Texture::GetTexture("src/Assets/Sprites/1_Industrial_Tileset_1.png");
		sr.SetTexture(tileTexture);
		sr.SubTexture(tileTexture, glm::vec2(48, 48), 32, 32);
	}

	//Ceiling
	for (int i = 0; i < 25; i++) {
		entt::entity tileEntity = CreateEntity(glm::vec3(-3.9f + (0.32 * i), 2.16f, 0.0f));

		AddComponent<StaticBox>(tileEntity).Init(0.32f, 0.32f);

		Sprite& sr = AddComponent<Sprite>(tileEntity);
		Texture tileTexture = Texture::GetTexture("src/Assets/Sprites/1_Industrial_Tileset_1.png");
		sr.SetTexture(tileTexture);
		if (i == 0) {
			sr.SubTexture(tileTexture, glm::vec2(144, 112), 32, 32);
		}
		else if (i == 24) {
			sr.SubTexture(tileTexture, glm::vec2(176, 112), 32, 32);
		}
		else {
			sr.SubTexture(tileTexture, glm::vec2(48, 16), 32, 32);
		}

	}

	for (int i = 0; i < 31; i++) {
		entt::entity tileEntity = CreateEntity(glm::vec3(-4.86f + (0.32 * i), 2.48f, 0.0f));

		AddComponent<StaticBox>(tileEntity).Init(0.32f, 0.32f);

		Sprite& sr = AddComponent<Sprite>(tileEntity);
		Texture tileTexture = Texture::GetTexture("src/Assets/Sprites/1_Industrial_Tileset_1.png");
		sr.SetTexture(tileTexture);
		sr.SubTexture(tileTexture, glm::vec2(48, 48), 32, 32);
	}

	for (int i = 0; i < 31; i++) {
		entt::entity tileEntity = CreateEntity(glm::vec3(-4.86f + (0.32 * i), 2.8f, 0.0f));

		AddComponent<StaticBox>(tileEntity).Init(0.32f, 0.32f);

		Sprite& sr = AddComponent<Sprite>(tileEntity);
		Texture tileTexture = Texture::GetTexture("src/Assets/Sprites/1_Industrial_Tileset_1.png");
		sr.SetTexture(tileTexture);
		sr.SubTexture(tileTexture, glm::vec2(48, 48), 32, 32);
	}

	//Low Left Ledge
	for (int i = 0; i < 15; i++) {
		entt::entity tileEntity = CreateEntity(glm::vec3(-3.9f + (0.32 * i), -0.4f, 0.0f));

		AddComponent<StaticBox>(tileEntity).Init(0.32f, 0.32f);

		Sprite& sr = AddComponent<Sprite>(tileEntity);
		Texture tileTexture = Texture::GetTexture("src/Assets/Sprites/1_Industrial_Tileset_1.png");
		sr.SetTexture(tileTexture);
		if (i == 0) {
			sr.SubTexture(tileTexture, glm::vec2(144, 80), 32, 32);
		}
		else if (i == 14) {
			sr.SubTexture(tileTexture, glm::vec2(80, 112), 32, 32);
		}
		else {
			sr.SubTexture(tileTexture, glm::vec2(48, 80), 32, 32);
		}

	}

	for (int i = 0; i < 3; i++) {
		entt::entity tileEntity = CreateEntity(glm::vec3(3.14f + (0.32 * i), -1.36f, 0.0f));

		AddComponent<StaticBox>(tileEntity).Init(0.32f, 0.32f);

		Sprite& sr = AddComponent<Sprite>(tileEntity);
		Texture tileTexture = Texture::GetTexture("src/Assets/Sprites/1_Industrial_Tileset_1.png");
		sr.SetTexture(tileTexture);
		if (i == 0) {
			sr.SubTexture(tileTexture, glm::vec2(16, 112), 32, 32);
		}
		else if (i == 2) {
			sr.SubTexture(tileTexture, glm::vec2(144, 48), 32, 32);
		}
		else {
			sr.SubTexture(tileTexture, glm::vec2(48, 80), 32, 32);
		}

	}

	for (int i = 0; i < 1; i++) {
		entt::entity tileEntity = CreateEntity(glm::vec3(1.86f + (0.32 * i), -0.72f, 0.0f));

		AddComponent<StaticBox>(tileEntity).Init(0.32f, 0.32f);

		Sprite& sr = AddComponent<Sprite>(tileEntity);
		Texture tileTexture = Texture::GetTexture("src/Assets/Sprites/1_Industrial_Tileset_1.png");
		sr.SetTexture(tileTexture);
		sr.SubTexture(tileTexture, glm::vec2(112, 112), 32, 32);
	}

}
