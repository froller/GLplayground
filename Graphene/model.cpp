#include "graphene.h"
#include <array>
#include <algorithm>

void Graphene::Model::addPrimitive(const Vertex a, const Vertex b, const Vertex c)
{
    addPrimitive({ a, b, c });
}

void Graphene::Model::addPrimitive(const std::array<Vertex, 3> vertices)
{
    std::array<unsigned int, 3> primitive;
    for (int i = 0; i < 3; ++i)
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

size_t Graphene::Model::vertexCount() const
{
    return m_Vertices.size();
}

size_t Graphene::Model::elementCount() const
{
    return m_Primitives.size();
}

size_t Graphene::Model::VBOsize() const
{
    return m_Vertices.size() * sizeof(Vertex);
}

size_t Graphene::Model::EBOsize() const
{
    return m_Primitives.size() * sizeof(Element);
}

size_t Graphene::Model::SSBOsize() const
{
    return sizeof(fmat4);
}

size_t Graphene::Model::VBOdata(void *vertexBuffer) const
{
    const size_t s = VBOsize();
    memcpy(vertexBuffer, m_Vertices.data(), s);
    return s;
}

size_t Graphene::Model::EBOdata(void *elementBuffer, GLsizei offset) const
{
    void *bufferTop = elementBuffer;
    for (auto i = m_Primitives.begin(); i != m_Primitives.end(); ++i)
    {
        for (unsigned int j = 0; j < ElementSize; ++j)
            (*static_cast<Element *>(bufferTop))[j] = (*i)[j] + offset;
        bufferTop = static_cast<Element *>(bufferTop) + 1;
    }
    return static_cast<uint8_t *>(bufferTop) - static_cast<uint8_t *>(elementBuffer);
}

size_t Graphene::Model::SSBOdata(void *storageBuffer) const
{
    const size_t s = SSBOsize();
    *(fmat4 *)storageBuffer = transform();
    return s;
}

void Graphene::Model::material(std::shared_ptr<Graphene::Material> material)
{
    m_Material = material;
}

std::shared_ptr<Graphene::Material> Graphene::Model::material() const
{
    return m_Material;
}
