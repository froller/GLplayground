#version 460 core

struct Vertex {
    vec3 position;
    vec3 normal;
    vec3 color;
    vec2 UV;
};

in Vertex vertex;
in flat uint vertexMeshId;

layout ( vertices = 3 ) out;

void main ()
{                                       // copy current vertex to output
    gl_out [gl_InvocationID].gl_Position = gl_in [gl_InvocationID].gl_Position;
    
    if ( gl_InvocationID == 0 )         // set tessellation level, can do only for one vertex
    {
        gl_TessLevelInner [0] = 2;
        gl_TessLevelOuter [0] = 2;
        gl_TessLevelOuter [1] = 2;
        gl_TessLevelOuter [2] = 2;
    }
}

