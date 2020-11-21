#version 460 core

struct Vertex {
    vec3 position;
    vec3 normal;
    vec3 color;
};

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexNormal;
layout(location = 2) in vec3 vertexColor;

out Vertex vertex;

uniform mat4 MVP[3];

void main()
{
    gl_Position = MVP[2] * MVP[1] * MVP[0] * vec4(vertexPosition, 1);
    vertex.position = vertexPosition;
    vertex.normal = vertexNormal;
    vertex.color = vertexColor;
}
