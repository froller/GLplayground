#version 460 core

uniform vec3 ambientColor;

in vec3 fragmentColor;
out vec3 color;

void main()
{
    color = fragmentColor;
}
