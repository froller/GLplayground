#version 460 core

uniform mat4 MVP[3];
layout(location = 0) in vec3 vertexPosition;

void main()
{
    gl_Position = MVP[2] * MVP[1] * MVP[0] * vec4(vertexPosition, 0);
}
