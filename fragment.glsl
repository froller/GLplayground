#version 460 core

in vec3 position;
in vec3 normal;
in vec3 color;

uniform mat4 MVP[3];
uniform vec3 cameraPos;
uniform vec3 ambientColor;
uniform uint lightsCount;

layout (std430, binding = 0) buffer Lights {
    vec3 position;
    vec3 color;
} lights[16];

out vec3 fragmentColor;

void main()
{
    vec3 ambient  = ambientColor * color;
    vec3 diffuse = vec3(0, 0, 0);
    vec3 specular = vec3(0, 0, 0);
    for (uint i = 0; i < lightsCount; ++i)
    {
        diffuse = diffuse + dot(normal, normalize(lights[i].position - position)) * lights[i].color;
        //specular = specular + (0.5 * pow(max(dot(normalize(cameraPos - position), reflect(-lights[i].position, normal)), 0.0), 32) * lights[i].color);
    }
    fragmentColor = (specular + diffuse + ambientColor);
}
