#version 460 core

struct Vertex {
    vec3 position;
    vec3 normal;
    vec3 color;
    vec2 UV;
};

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec3 color;
layout(location = 3) in vec2 UV;
layout(location = 4) in uint meshId;

out Vertex vertex;
out flat uint meshIdOut;

uniform mat4 MVP[3];

void main()
{
    gl_Position = MVP[2] * MVP[1] * MVP[0] * vec4(position, 1);
    vertex.position = position;
    vertex.normal = normal;
    vertex.color = color;
    vertex.UV = UV;
    meshIdOut = meshId;
}
