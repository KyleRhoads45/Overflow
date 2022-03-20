#include "AnimationController.h"
#include <iostream>

Animation::Animation(const Texture& texture, float fps, int cellWidth, int cellHeight, int count, int startOffset)
: texture(texture), fps(fps), cellWidth(cellWidth), cellHeight(cellHeight) {

	const int rowCount = texture.height / cellHeight;
	const int colCount = texture.width / cellWidth;

	int curOffset = startOffset;
	for (int i = 0; i < count; i++) {
		int row = curOffset / colCount;
		int col = curOffset % colCount;

		int x = (cellWidth * col) + cellWidth / 2;
		int y = (texture.height - (cellHeight * row)) - cellHeight / 2;

		centers.push_back(glm::vec2(x, y));
		curOffset++;
	}
}