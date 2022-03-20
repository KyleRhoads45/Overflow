#version 460 core

layout (location = 0) in vec3 iPos;
layout (location = 1) in vec2 iTexCoord;
layout (location = 2) in float iTexIndex;

uniform mat4 view; 
uniform mat4 projection; 

out vec2 texCoord;
out float texIndex;

void main() {
	texCoord = iTexCoord;
	texIndex = iTexIndex;
	gl_Position = projection * view * vec4(iPos, 1.0f);
}