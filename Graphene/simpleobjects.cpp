#include "graphene.h"
#include <math.h>

Graphene::SimpleObjects::Triangle::Triangle()
{
    m_Vertices.push_back(fvec3(0.f, 1.f, 0.f));
    m_Vertices.push_back(fvec3(sqrtf(3.f) / -2.f, -0.5f, 0.f));
    m_Vertices.push_back(fvec3(sqrtf(3.f) / 2.f, -0.5f, 0.f));
    m_Primitives.push_back(std::array<unsigned int, 3>({1, 2, 3}));
}

Graphene::SimpleObjects::Square::Square()
{
    m_Vertices.push_back(fvec3(-1.f, -1.f, 0.f));
    m_Vertices.push_back(fvec3(-1.f,  1.f, 0.f));
    m_Vertices.push_back(fvec3( 1.f,  1.f, 0.f));
    m_Vertices.push_back(fvec3( 1.f, -1.f, 0.f));
    m_Primitives.push_back(std::array<unsigned int, 3>({1, 3, 2}));
    m_Primitives.push_back(std::array<unsigned int, 3>({1, 4, 2}));
}
