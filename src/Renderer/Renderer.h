#pragma once
#include <glfw/glfw3.h>
#include "../Core/Scene.h"
#include "Shader.h"
#include "Vertex.h"

class Renderer {

public:

	static void Init();
	static void RenderScene(Scene& scene);
	static void EndFrame(GLFWwindow* window);

	static void DebugDrawRect(const glm::vec2& pos, const float width, const float height);
	static void DebugDrawCircle(const glm::vec2& pos, const float radius);

private:

	static void DrawSprite(const Transform& trans, const Sprite& sprite);
	static void FlushRenderBuffer();

	static unsigned int gizmosVao;
	static unsigned int gizmosVbo;
};
