#include "graphene.h"
#include <math.h>
#include <array>

#define VERTEX(x,y,z,r,g,b) {position: fvec3(x, y, z), color: fvec3(r, g, b)}
#define ELEMENT(a,b,c) {a, b, c}

Graphene::SimpleObjects::Triangle::Triangle()
{
    m_Vertices.push_back(VERTEX(0.f,                1.f,  0.f, 0.f, 1.f, 0.f));
    m_Vertices.push_back(VERTEX(sqrtf(3.f) / -2.f, -0.5f, 0.f, 0.f, 1.f, 0.f));
    m_Vertices.push_back(VERTEX(sqrtf(3.f) /  2.f, -0.5f, 0.f, 0.f, 1.f, 0.f));
    m_Primitives.push_back(ELEMENT(0, 1, 2));
}

Graphene::SimpleObjects::Square::Square()
{
    m_Vertices.push_back(VERTEX(-1.f, -1.f, 0.f, 1.f, 0.f, 0.f));
    m_Vertices.push_back(VERTEX(-1.f,  1.f, 0.f, 1.f, 0.f, 0.f));
    m_Vertices.push_back(VERTEX( 1.f,  1.f, 0.f, 1.f, 0.f, 0.f));
    m_Vertices.push_back(VERTEX( 1.f, -1.f, 0.f, 1.f, 0.f, 0.f));
    m_Primitives.push_back(ELEMENT(0, 2, 1));
    m_Primitives.push_back(ELEMENT(0, 2, 3));
}

Graphene::SimpleObjects::Tetrahedron::Tetrahedron()
{
    m_Vertices.push_back(VERTEX(             -1.f,             -1.f,  0.f, 0.f, 0.5, 1.f));
    m_Vertices.push_back(VERTEX(sqrtf(3.f) / -2.f, sqrt(3.f) / -4.f, -0.5, 0.f, 0.5, 1.f));
    m_Vertices.push_back(VERTEX(sqrtf(3.f) /  2.f, sqrt(3.f) / -4.f, -0.5, 0.f, 0.5, 1.f));
    m_Vertices.push_back(VERTEX(0.f,               sqrt(3.f) / -4.f,  1.f, 0.f, 0.5, 1.f));
    m_Primitives.push_back(ELEMENT(0, 2, 1));
    m_Primitives.push_back(ELEMENT(0, 3, 2));
    m_Primitives.push_back(ELEMENT(0, 1, 4));
    m_Primitives.push_back(ELEMENT(1, 3, 2));
}

#undef ELEMENT
#undef VERTEX
