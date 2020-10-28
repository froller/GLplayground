#include "graphene.h"
#include <array>
#include <algorithm>

void Graphene::Model::addPrimitive(const fvec3 a, const fvec3 b, const fvec3 c)
{
    addPrimitive({a, b, c});
}

void Graphene::Model::addPrimitive ( const std::array<fvec3, 3> vertices )
{
    std::array<unsigned int, 3> primitive;
    for (char i = 0; i < 3; ++i)
    {
        auto vertex = std::find(m_Vertices.begin(), m_Vertices.end(), vertices[i]);
        if (vertex == m_Vertices.end())
        {
            m_Vertices.push_back(vertices[i]);
            vertex = m_Vertices.end() - 1;
        }
        primitive[i] = m_Vertices.begin() - vertex;
    }
    m_Primitives.push_back(primitive);
}

const size_t Graphene::Model::VBOsize() const
{
    return m_Vertices.size() * sizeof(fvec3);
}

const void *Graphene::Model::VBO() const
{
    return m_Vertices.data();
}

const size_t Graphene::Model::EBOsize() const
{
    return m_Primitives.size() * 3 * sizeof(const unsigned int);
}

const void *Graphene::Model::EBO() const
{
    return reinterpret_cast<const unsigned int *>(m_Primitives.data());
}
