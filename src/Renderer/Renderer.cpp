#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../Components/Components.h"
#include "Shader.h"
#include "Renderer.h"
#include <iostream>

static const int maxTextureSlots = 32;
static const int MaxQuadCount = 1000;
static const int MaxVertCount = MaxQuadCount * 4;
static const int MaxIndexCount = MaxQuadCount * 6;

static struct RenderBuffer {
	unsigned int vao;
	unsigned int vbo;
	unsigned int ebo;
	int curQuadSize = 0;

	int vertIndex = 0;
	Vertex verts[MaxVertCount];

	int texIndex = 0;
	unsigned int textureIds[maxTextureSlots];
};

static std::unique_ptr<Shader> standardShader;
static std::unique_ptr<Shader> gizmosShader;
static RenderBuffer renderBuffer;

unsigned int gizmosVao;
unsigned int gizmosVbo;

static void DrawSprite(const Transform& trans, const Sprite& sprite);
static void FlushRenderBuffer();

void RendererInit() {
	glEnable(GL_CULL_FACE);
	glDisable(GL_MULTISAMPLE);

	standardShader = std::make_unique<Shader>("src/Assets/Shaders/Standard.vert", "src/Assets/Shaders/Standard.frag");
	gizmosShader = std::make_unique<Shader>("src/Assets/Shaders/Gizmos.vert", "src/Assets/Shaders/Gizmos.frag");

    int samplers[32];
    for (int i = 0; i < 32; i++) {
        samplers[i] = i;
    }
    glUseProgram(standardShader->id);
    glUniform1iv(glGetUniformLocation(standardShader->id, "textures"), 32, samplers);

	//Render buffer
	renderBuffer.curQuadSize = 0;
	renderBuffer.texIndex = 0;
	renderBuffer.vertIndex = 0;

	glGenVertexArrays(1, &renderBuffer.vao);
	glBindVertexArray(renderBuffer.vao);

	glGenBuffers(1, &renderBuffer.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, renderBuffer.vbo);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, textureIndex));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	int offset = 0;
	unsigned int* indicies = new unsigned int[MaxIndexCount];
	for (int i = 0; i < MaxIndexCount; i += 6) {
		indicies[i + 0] = 0 + offset;
		indicies[i + 1] = 1 + offset;
		indicies[i + 2] = 2 + offset;
		indicies[i + 3] = 2 + offset;
		indicies[i + 4] = 3 + offset;
		indicies[i + 5] = 0 + offset;

		offset += 4;
	}

	glGenBuffers(1, &renderBuffer.ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderBuffer.ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * MaxIndexCount, indicies, GL_STATIC_DRAW);

	delete[] indicies;

	//Unbind render buffers
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//Gizmos
	glGenVertexArrays(1, &gizmosVao);
	glBindVertexArray(gizmosVao);

	glGenBuffers(1, &gizmosVbo);
	glBindBuffer(GL_ARRAY_BUFFER, gizmosVbo);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0);
	glEnableVertexAttribArray(0);

	//Unbind gizmo buffers
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void RendererRenderScene(Scene& scene) {
	glEnable(GL_DEPTH_TEST);
	glUseProgram(standardShader->id);

	const auto& renderView = scene.registry.view<Transform, Sprite>();
	for (const auto& [entity, trans, sprite] : renderView.each()) {
		DrawSprite(trans, sprite);
		if (renderBuffer.curQuadSize >= MaxQuadCount) {
			FlushRenderBuffer();
		}
	}

	FlushRenderBuffer();
}

void RendererEndFrame(GLFWwindow* window) {
	glfwSwapBuffers(window);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1, 1, 1, 1);
}

void RendererDebugDrawRect(const glm::vec2& pos, const float width, const float height) {
	glDisable(GL_DEPTH_TEST);
	glUseProgram(gizmosShader->id);

	glBindVertexArray(gizmosVao);
	glBindBuffer(GL_ARRAY_BUFFER, gizmosVbo);

	glm::vec2 boxVerts[4];
	float halfWidth = width / 2.0f;
	float halfHeight = height / 2.0f;

	boxVerts[0] = glm::vec2(pos.x - halfWidth, pos.y - halfHeight);
	boxVerts[1] = glm::vec2(pos.x + halfWidth, pos.y - halfHeight);
	boxVerts[2] = glm::vec2(pos.x + halfWidth, pos.y + halfHeight);
	boxVerts[3] = glm::vec2(pos.x - halfWidth, pos.y + halfHeight);

	Camera* mainCam = Camera::mainCam;
	glUniformMatrix4fv(glGetUniformLocation(gizmosShader->id, "view"), 1, GL_FALSE, glm::value_ptr(mainCam->view));
	glUniformMatrix4fv(glGetUniformLocation(gizmosShader->id, "projection"), 1, GL_FALSE, glm::value_ptr(mainCam->projection));

	glBufferData(GL_ARRAY_BUFFER, sizeof(boxVerts), &boxVerts, GL_DYNAMIC_DRAW);
	glDrawArrays(GL_LINE_LOOP, 0, 4);
}

void RendererDebugDrawCircle(const glm::vec2& pos, const float radius) {
	glDisable(GL_DEPTH_TEST);
	glUseProgram(gizmosShader->id);

	glBindVertexArray(gizmosVao);
	glBindBuffer(GL_ARRAY_BUFFER, gizmosVbo);

	const int circleVertCount = 30;
	constexpr float interval = (2.0f * glm::pi<float>()) / circleVertCount;

	glm::vec2 circleVerts[circleVertCount];

	float curProgress = 0.0f;
	for (int i = 0; i < circleVertCount; i++) {
		float x = glm::cos(curProgress) * radius;
		float y = glm::sin(curProgress) * radius;
		circleVerts[i] = glm::vec2(pos.x, pos.y) + glm::vec2(x, y);
		curProgress += interval;
	}

	Camera* mainCam = Camera::mainCam;
	glUniformMatrix4fv(glGetUniformLocation(gizmosShader->id, "view"), 1, GL_FALSE, glm::value_ptr(mainCam->view));
	glUniformMatrix4fv(glGetUniformLocation(gizmosShader->id, "projection"), 1, GL_FALSE, glm::value_ptr(mainCam->projection));

	glBufferData(GL_ARRAY_BUFFER, sizeof(circleVerts), &circleVerts, GL_DYNAMIC_DRAW);
	glDrawArrays(GL_LINE_LOOP, 0, circleVertCount);
}

static void DrawSprite(const Transform& trans, const Sprite& sprite) {
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, trans.position);
	model = glm::scale(model, trans.scale);
	model = glm::rotate(model, glm::radians(trans.rotation), glm::vec3(0, 0, 1));

	int vertTexIndex = -1;
	if (renderBuffer.texIndex != 0) {
		for (int i = 0; i < renderBuffer.texIndex; i++) {
			if (renderBuffer.textureIds[i] == sprite.textureId) {
				vertTexIndex = i;
				break;
			}
		}
	}

	if (vertTexIndex == -1) {
		renderBuffer.textureIds[renderBuffer.texIndex] = sprite.textureId;
		glActiveTexture(GL_TEXTURE0 + renderBuffer.texIndex);
		glBindTexture(GL_TEXTURE_2D, sprite.textureId);
		vertTexIndex = renderBuffer.texIndex;
		renderBuffer.texIndex++;
	}

	for (int i = 0; i < 4; i++) {
		Vertex worldVert = sprite.verts[i];
		glm::vec4 temp = model * glm::vec4(worldVert.position.x, worldVert.position.y, 0.0f, 1.0f);

		worldVert.position.x = temp.x;
		worldVert.position.y = temp.y;
		worldVert.position.z = temp.z;

		worldVert.texCoord = sprite.verts[i].texCoord;
		worldVert.textureIndex = vertTexIndex;

		renderBuffer.verts[renderBuffer.vertIndex] = worldVert;
		renderBuffer.vertIndex++;
	}

	renderBuffer.curQuadSize++;
}

static void FlushRenderBuffer() {
	glBindVertexArray(renderBuffer.vao);

	glBindBuffer(GL_ARRAY_BUFFER, renderBuffer.vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(renderBuffer.verts), renderBuffer.verts, GL_DYNAMIC_DRAW);

	Camera* mainCam = Camera::mainCam;
	glUniformMatrix4fv(glGetUniformLocation(standardShader->id, "view"), 1, GL_FALSE, glm::value_ptr(mainCam->view));
	glUniformMatrix4fv(glGetUniformLocation(standardShader->id, "projection"), 1, GL_FALSE, glm::value_ptr(mainCam->projection));

	glDrawElements(GL_TRIANGLES, renderBuffer.curQuadSize * 6, GL_UNSIGNED_INT, 0);

	renderBuffer.curQuadSize = 0;
	renderBuffer.texIndex = 0;
	renderBuffer.vertIndex = 0;
}
