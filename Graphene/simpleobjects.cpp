#include "graphene.h"
#include <math.h>

Graphene::SimpleObjects::Triangle::Triangle()
{
    m_Vertices.push_back(fvec3(0.f, 1.f, 0.f));
    m_Vertices.push_back(fvec3(sqrtf(3.f) / -2.f, -0.5f, 0.f));
    m_Vertices.push_back(fvec3(sqrtf(3.f) / 2.f, -0.5f, 0.f));
    m_Primitives.push_back(std::array<unsigned int, 3>({0, 1, 2}));
}

Graphene::SimpleObjects::Square::Square()
{
    m_Vertices.push_back(fvec3(-1.f, -1.f, 0.f));
    m_Vertices.push_back(fvec3(-1.f,  1.f, 0.f));
    m_Vertices.push_back(fvec3( 1.f,  1.f, 0.f));
    m_Vertices.push_back(fvec3( 1.f, -1.f, 0.f));
    m_Primitives.push_back(std::array<unsigned int, 3>({0, 2, 1}));
    m_Primitives.push_back(std::array<unsigned int, 3>({0, 3, 1}));
}

Graphene::SimpleObjects::Tetrahedron::Tetrahedron()
{
    m_Vertices.push_back(fvec3(-1.f, -1.f, 0.f));
    m_Vertices.push_back(fvec3(sqrtf(3.f) / -2.f, sqrt(3.f) / -4.f, -0.5f));
    m_Vertices.push_back(fvec3(sqrtf(3.f) /  2.f, sqrt(3.f) / -4.f, -0.5f));
    m_Vertices.push_back(fvec3(0.f,               sqrt(3.f) / -4.f,  1.f));
    m_Primitives.push_back(std::array<unsigned int, 3>({0, 2, 1}));
    m_Primitives.push_back(std::array<unsigned int, 3>({0, 3, 2}));
    m_Primitives.push_back(std::array<unsigned int, 3>({0, 1, 4}));
    m_Primitives.push_back(std::array<unsigned int, 3>({1, 3, 2}));
}
