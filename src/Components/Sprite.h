#pragma once
#include <glm/glm.hpp>
#include "../Renderer/Texture.h"
#include "../Renderer/Vertex.h"

struct Sprite {
	Vertex verts[4];
	unsigned int textureId;
	bool flipped = false;

	void Flip(bool doFlip);
	void SetTexture(const Texture& texture);
	void SubTexture(const Texture& texture, const glm::vec2& center, int cellWidth, int cellHeight);
};
