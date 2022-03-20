#pragma once

struct Texture {
	
	int width;
	int height;
	unsigned int id;

	static Texture GetTexture(const char* texturePath);

};

