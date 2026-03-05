#version 460 core

layout (location = 0) in vec3 vertexPos;
layout (location = 1) in vec3 colour;

out vec3 fragmentColor;

vec3 vertexColor = vec3(0.3f, 0.6f, 1.0f);

void main(){
    gl_Position = vec4(vertexPos, 1.0);
    fragmentColor = colour;
}