#version 430 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec4 colors;

out vec4 vFragColorVs;

void main() {
   vFragColorVs = colors;
   gl_Position = vec4(position, 0.0f, 1.0f);
}
