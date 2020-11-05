#version 460 core

uniform vec3 ambientColor;

in vec3 normal;
in vec3 color;

out vec3 fragmentColor;

void main()
{
    fragmentColor = ambientColor * color;
}
