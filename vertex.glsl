#version 460 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexNormal;
layout(location = 2) in vec3 vertexColor;

uniform mat4 MVP[3];

//out vec2 UV;
out vec3 fragmentColor;

void main()
{
//    gl_Position.xyz = vertexPosition;
//    gl_Position.w = 1.0;

    gl_Position = MVP[2] * MVP[1] * MVP[0] * vec4(vertexPosition, 1);
    fragmentColor = vertexColor;
}
