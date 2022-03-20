#include <iostream>
#include <unordered_map>
#include <glad/glad.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include "Texture.h"
	
static std::unordered_map<const char*, Texture> loadedTexturePool;

Texture Texture::GetTexture(const char* texturePath) {
	if (loadedTexturePool.find(texturePath) != loadedTexturePool.end()) {
		return loadedTexturePool[texturePath];
	}

	Texture newTexture;

	stbi_set_flip_vertically_on_load(true);

	int numChannels;
	unsigned char* imageData = stbi_load(texturePath, &newTexture.width, &newTexture.height, &numChannels, 0);

	if (!imageData) {
		std::cout << "Failed to load texture" << std::endl;
	}

	glGenTextures(1, &newTexture.id);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, newTexture.id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	if (numChannels == 4) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, newTexture.width, newTexture.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
	}
	else {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, newTexture.width, newTexture.height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
	}

	stbi_image_free(imageData);
	loadedTexturePool[texturePath] = newTexture;

	return newTexture;
}
