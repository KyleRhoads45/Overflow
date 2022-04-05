#pragma once
#include <glfw/glfw3.h>
#include "../Core/Scene.h"
#include "Shader.h"
#include "Vertex.h"

void RendererInit();
void RendererRenderScene(Scene& scene);
void RendererEndFrame(GLFWwindow* window);
void RendererDebugDrawRect(const glm::vec2& pos, const float width, const float height);
void RendererDebugDrawCircle(const glm::vec2& pos, const float radius);
