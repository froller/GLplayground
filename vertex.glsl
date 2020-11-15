#version 460 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexNormal;
layout(location = 2) in vec3 vertexColor;

//out vec2 UV;
out vec3 position;
out vec3 normal;
out vec3 color;

uniform mat4 MVP[3];

void main()
{
    gl_Position = MVP[2] * MVP[1] * MVP[0] * vec4(vertexPosition, 1);
    position = vertexPosition;
    normal = vertexNormal;
    color = vertexColor;
}
