#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <stb/stb_image.h>
#include "Sprite.h"

static void ForceFlip(Vertex verts[]) {
	glm::vec2 swapCoord = verts[0].texCoord;
	verts[0].texCoord = verts[1].texCoord;
	verts[1].texCoord = swapCoord;

	swapCoord = verts[2].texCoord;
	verts[2].texCoord = verts[3].texCoord;
	verts[3].texCoord = swapCoord;
}

void Sprite::Flip(bool doFlip) {
	if (flipped == doFlip) return;
	flipped = doFlip;

	glm::vec2 swapCoord = verts[0].texCoord;
	verts[0].texCoord = verts[1].texCoord;
	verts[1].texCoord = swapCoord;

	swapCoord = verts[2].texCoord;
	verts[2].texCoord = verts[3].texCoord;
	verts[3].texCoord = swapCoord;
}

void Sprite::SetTexture(const Texture& texture) {
	textureId = texture.id;

	const int pixelsPerUnit = 100;
	float halfWidth = (texture.width / 2.0f) / pixelsPerUnit;
	float halfHeight = (texture.height / 2.0f) / pixelsPerUnit;

	Vertex bottomLeft;
	bottomLeft.position.x = -halfWidth;
	bottomLeft.position.y = -halfHeight;
	bottomLeft.texCoord.x = 0.0f;
	bottomLeft.texCoord.y = 0.0f;

	Vertex bottomRight;
	bottomRight.position.x = halfWidth;
	bottomRight.position.y = -halfHeight;
	bottomRight.texCoord.x = 1.0f;
	bottomRight.texCoord.y = 0.0f;

	Vertex topRight;
	topRight.position.x = halfWidth;
	topRight.position.y = halfHeight;
	topRight.texCoord.x = 1.0f;
	topRight.texCoord.y = 1.0f;

	Vertex topLeft;
	topLeft.position.x = -halfWidth;
	topLeft.position.y = halfHeight;
	topLeft.texCoord.x = 0.0f;
	topLeft.texCoord.y = 1.0f;

	verts[0] = bottomLeft;
	verts[1] = bottomRight;
	verts[2] = topRight;
	verts[3] = topLeft;

	if (flipped) {
		ForceFlip(verts);
	}
}

void Sprite::SubTexture(const Texture& texture, const glm::vec2& center, int cellWidth, int cellHeight) {
	const int pixelsPerUnit = 100;
	const float halfWidth = (cellWidth / 2.0f) / pixelsPerUnit;
	const float halfHeight = (cellHeight / 2.0f) / pixelsPerUnit;

	const float halfCellWidth = cellWidth / 2.0f;
	const float halfCellHeight = cellHeight / 2.0f;

	Vertex bottomLeft;
	bottomLeft.position.x = -halfWidth;
	bottomLeft.position.y = -halfHeight;
	bottomLeft.texCoord.x = (center.x - halfCellWidth) / texture.width;
	bottomLeft.texCoord.y = (center.y - halfCellHeight) / texture.height;

	Vertex bottomRight;
	bottomRight.position.x = halfWidth;
	bottomRight.position.y = -halfHeight;
	bottomRight.texCoord.x = (center.x + halfCellWidth) / texture.width;
	bottomRight.texCoord.y = (center.y - halfCellHeight) / texture.height;

	Vertex topRight;
	topRight.position.x = halfWidth;
	topRight.position.y = halfHeight;
	topRight.texCoord.x = (center.x + halfCellWidth) / texture.width;
	topRight.texCoord.y = (center.y + halfCellHeight) / texture.height;

	Vertex topLeft;
	topLeft.position.x = -halfWidth;
	topLeft.position.y = halfHeight;
	topLeft.texCoord.x = (center.x - halfCellWidth) / texture.width;
	topLeft.texCoord.y = (center.y + halfCellHeight) / texture.height;

	verts[0] = bottomLeft;
	verts[1] = bottomRight;
	verts[2] = topRight;
	verts[3] = topLeft;

	if (flipped) {
		ForceFlip(verts);
	}
}
