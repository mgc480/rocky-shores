#version 330 core

layout(location = 0) in vec3 vertexPosition_ms;
layout(location = 1) in vec3 vertexColor;

out vec3 fragmentColor;    //outputs color to fragment shader
uniform mat4 MVP;

void main(){

    gl_Position.xyz = vertexPosition_ms;
    gl_Position.w = 1.0;

    fragmentColor = vertexColor;
}