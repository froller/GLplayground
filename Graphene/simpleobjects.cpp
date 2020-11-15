#include "graphene.h"
#include <math.h>
#include <array>

#define VERTEX(x,y,z,nx,ny,nz,r,g,b) m_Vertices.push_back({position: fvec3(x, y, z), normal: fvec3(nx, ny, nz), color: fvec3(r, g, b)})
#define ELEMENT(a,b,c) m_Primitives.push_back({a, b, c})

Graphene::SimpleObjects::Triangle::Triangle()
{
    VERTEX( 0.f,  1.f / sqrtf(3.f), 0.f,   0.f, 0.f, -1.f,   0.f, 1.f, 0.f);
    VERTEX(-0.5, -0.5 / sqrtf(3.f), 0.f,   0.f, 0.f, -1.f,   0.f, 1.f, 0.f);
    VERTEX( 0.5, -0.5 / sqrtf(3.f), 0.f,   0.f, 0.f, -1.f,   0.f, 1.f, 0.f);
    ELEMENT(0, 1, 2);
}

Graphene::SimpleObjects::Square::Square()
{
    VERTEX(-0.5, -0.5, 0.f,   0.f, 0.f, -1.f,   1.f, 1.f, 1.f);
    VERTEX(-0.5,  0.5, 0.f,   0.f, 0.f, -1.f,   1.f, 1.f, 1.f);
    VERTEX( 0.5,  0.5, 0.f,   0.f, 0.f, -1.f,   1.f, 1.f, 1.f);
    VERTEX( 0.5, -0.5, 0.f,   0.f, 0.f, -1.f,   1.f, 1.f, 1.f);
    ELEMENT(0, 2, 1);
    ELEMENT(0, 2, 3);
}

/*
Graphene::SimpleObjects::Tetrahedron::Tetrahedron()
{
    VERTEX( 0.f,  sqrtf(6.f) / -12.f,  1.f / sqrtf(3.f),    0.f,  sqrtf(6.f) / -12.f,  1.f / sqrtf(3.f),   0.f, 1.f, 1.f); // передний
    VERTEX(-0.5,  sqrtf(6.f) / -12.f, -0.5 / sqrtf(3.f),   -0.5,  sqrtf(6.f) / -12.f, -0.5 / sqrtf(3.f),   0.f, 1.f, 1.f); // левый
    VERTEX( 0.5,  sqrtf(6.f) / -12.f, -0.5 / sqrtf(3.f),    0.5,  sqrtf(6.f) / -12.f, -0.5 / sqrtf(3.f),   0.f, 1.f, 1.f); // правый
    VERTEX( 0.f,  1.f / sqrtf(3.f),   -0.f,                 0.f,  1.f / sqrtf(3.f),   -0.f,                0.f, 1.f, 1.f); // верхний

    ELEMENT(0, 1, 2);
    ELEMENT(0, 3, 1);
    ELEMENT(2, 3, 0);
    ELEMENT(1, 3, 2);
}
*/

Graphene::SimpleObjects::Tetrahedron::Tetrahedron()
{
    VERTEX( 0.f,  sqrtf(6.f) / -12.f, -1.f / sqrtf(3.f),    0.f, -1.f / sqrtf(3.f),    0.f,                1.f, 0.f, 0.f); // передний
    VERTEX(-0.5,  sqrtf(6.f) / -12.f,  0.5 / sqrtf(3.f),    0.f, -1.f / sqrtf(3.f),    0.f,                1.f, 0.f, 0.f); // левый
    VERTEX( 0.5,  sqrtf(6.f) / -12.f,  0.5 / sqrtf(3.f),    0.f, -1.f / sqrtf(3.f),    0.f,                1.f, 0.f, 0.f); // правый

    VERTEX( 0.f,  sqrtf(6.f) / -12.f, -1.f / sqrtf(3.f),   -0.5,  sqrtf(6.f) /  12.f, -0.5 / sqrtf(3.f),   1.f, 1.f, 0.f); // передний
    VERTEX( 0.f,  1.f / sqrtf(3.f),    0.f,                -0.5,  sqrtf(6.f) /  12.f, -0.5 / sqrtf(3.f),   1.f, 1.f, 0.f); // верхний
    VERTEX(-0.5,  sqrtf(6.f) / -12.f,  0.5 / sqrtf(3.f),   -0.5,  sqrtf(6.f) /  12.f, -0.5 / sqrtf(3.f),   1.f, 1.f, 0.f); // левый

    VERTEX(-0.5,  sqrtf(6.f) / -12.f,  0.5 / sqrtf(3.f),    0.f,  sqrtf(6.f) /  12.f,  1.f / sqrtf(3.f),   0.f, 1.f, 0.f); // левый
    VERTEX( 0.f,  1.f / sqrtf(3.f),    0.f,                 0.f,  sqrtf(6.f) /  12.f,  1.f / sqrtf(3.f),   0.f, 1.f, 0.f); // верхний
    VERTEX( 0.5,  sqrtf(6.f) / -12.f,  0.5 / sqrtf(3.f),    0.f,  sqrtf(6.f) /  12.f,  1.f / sqrtf(3.f),   0.f, 1.f, 0.f); // правый
  
    VERTEX( 0.5,  sqrtf(6.f) / -12.f,  0.5 / sqrtf(3.f),    0.5,  sqrtf(6.f) /  12.f, -0.5 / sqrtf(3.f),   0.f, 0.5, 1.f); // правый
    VERTEX( 0.f,  1.f / sqrtf(3.f),    0.f,                 0.5,  sqrtf(6.f) /  12.f, -0.5 / sqrtf(3.f),   0.f, 0.5, 1.f); // верхний
    VERTEX( 0.f,  sqrtf(6.f) / -12.f, -1.f / sqrtf(3.f),    0.5,  sqrtf(6.f) /  12.f, -0.5 / sqrtf(3.f),   0.f, 0.5, 1.f); // передний
    
    ELEMENT(0, 1, 2);
    ELEMENT(3, 4, 5);
    ELEMENT(6, 7, 8);
    ELEMENT(9, 10, 11);
}


#undef ELEMENT
#undef VERTEX
