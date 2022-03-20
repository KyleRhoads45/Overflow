#version 460 core

in vec2 texCoord;
in float texIndex;

uniform sampler2D textures[32];

out vec4 FragColor;

void main() {
    FragColor = texture(textures[int(texIndex)], texCoord);
    if(FragColor.a <= 0.1) {
       discard; 
    }
}