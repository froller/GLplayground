#version 460 core

in vec3 normal;
in vec3 color;

uniform vec3 ambientColor;
uniform int lightsCount;
layout (std430, binding = 0) buffer Lights {
    vec3 position;
    vec3 color;
} lights[4];

out vec3 fragmentColor;

void main()
{
    vec3 ambient  = ambientColor * color;
//    vec3 diffuse  = dot(normal, lights[0].position) * color;
    vec3 diffuse = vec3(0, 0, 0);
    for (int i = 0; i < 4; ++i)
        diffuse = diffuse + dot(normal, lights[i].position) * lights[i].color;
    vec3 specular = vec3(0, 0, 0);
    fragmentColor = ambient + diffuse + specular;
}
