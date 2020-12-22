#version 430 core

uniform vec3 color;

out vec4 result;

void main() {
	result = vec4(color, 1.0f);
}
