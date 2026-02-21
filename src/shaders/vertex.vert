#version 460 core

in vec2 vertexPos;

out vec3 fragmentColor;

vec3 vertexColor = vec3(0.3f, 0.6f, 1.0f);

void main(){
    gl_Position = vec4(vertexPos, 0.0 , 1.0);
    fragmentColor = vertexColor;
}