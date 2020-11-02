#version 460 core

layout(location = 0) in vec3 vertexPosition;

uniform mat4 MVP[3];

//out vec2 UV;

void main()
{
//    gl_Position.xyz = vertexPosition;
//    gl_Position.w = 1.0;

    gl_Position = MVP[2] * MVP[1] * MVP[0] * vec4(vertexPosition, 1);
}
