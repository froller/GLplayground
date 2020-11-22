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

layout(std140, binding = 0) uniform CameraMatrices {
    mat4 world;
    mat4 view;
    mat4 projection;
    vec3 position;
} cameraMatrices;

layout(std430, binding = 1) buffer Models {
    uint count;
    float reserved0;
    mat4 model[];
} models;

out Vertex vertex;
out flat uint vertexMeshId;

//uniform mat4 MVP[3];

void main()
{
    vertexMeshId = meshId;
    vertex.position = position;
    vertex.normal = normal;
    vertex.color = color;
    vertex.UV = UV;
    gl_Position = cameraMatrices.projection * cameraMatrices.view * cameraMatrices.world * models.model[vertexMeshId] * vec4(position, 1);
}
