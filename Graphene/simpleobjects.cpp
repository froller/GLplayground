#include "graphene.h"
#include <math.h>
#include <array>

#define VERTEX(x,y,z,nx,ny,nz,r,g,b) m_Vertices.push_back({fvec3(x, y, z), fvec3(nx, ny, nz), fvec3(r, g, b)})
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

Graphene::SimpleObjects::Cube::Cube()
{
    VERTEX(-0.5, -0.5, -0.5,    0.f, 0.f, -1.f,   1.f, 1.f, 1.f); // л н п
    VERTEX(-0.5,  0.5, -0.5,    0.f, 0.f, -1.f,   1.f, 1.f, 1.f); // л в п
    VERTEX( 0.5,  0.5, -0.5,    0.f, 0.f, -1.f,   1.f, 1.f, 1.f); // п в п
    VERTEX( 0.5, -0.5, -0.5,    0.f, 0.f, -1.f,   1.f, 1.f, 1.f); // п н п

    VERTEX(-0.5, -0.5,  0.5,    0.f, 0.f,  1.f,   1.f, 1.f, 1.f); // л н з
    VERTEX(-0.5,  0.5,  0.5,    0.f, 0.f,  1.f,   1.f, 1.f, 1.f); // л в з
    VERTEX( 0.5,  0.5,  0.5,    0.f, 0.f,  1.f,   1.f, 1.f, 1.f); // п в з
    VERTEX( 0.5, -0.5,  0.5,    0.f, 0.f,  1.f,   1.f, 1.f, 1.f); // п н з

    VERTEX(-0.5, -0.5, -0.5,   -1.f, 0.f,  0.f,   1.f, 1.f, 1.f); // л н п
    VERTEX(-0.5,  0.5, -0.5,   -1.f, 0.f,  0.f,   1.f, 1.f, 1.f); // л в п
    VERTEX(-0.5, -0.5,  0.5,   -1.f, 0.f,  0.f,   1.f, 1.f, 1.f); // л н з
    VERTEX(-0.5,  0.5,  0.5,   -1.f, 0.f,  0.f,   1.f, 1.f, 1.f); // л в з


    ELEMENT(0, 2, 1);
    ELEMENT(0, 2, 3);

    ELEMENT(6, 4, 5);
    ELEMENT(6, 4, 7);

    ELEMENT(8, 9, 10);
    ELEMENT(10, 9, 11);
}

#undef ELEMENT
#undef VERTEX

