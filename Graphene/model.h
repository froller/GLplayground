#ifndef __MODEL_H__
#define __MODEL_H__

/*******************************************************************************
 * 
 * Graphene::Model
 * 
 ******************************************************************************/

class Graphene::Model : public Graphene::Object
{
public:
    std::vector<Vertex> m_Vertices;
    std::vector<std::array<unsigned int, 3>> m_Primitives;
public:
    Model() = default;
    virtual ~Model() = default;
    //virtual load(cont std::filesystem::path &path);
    virtual void addPrimitive(const Vertex a, const Vertex b, const Vertex c);
    virtual void addPrimitive(const std::array<Vertex, 3> vertices);
    virtual size_t vertexCount() const;
    virtual size_t elementCount() const;
    virtual size_t VBOsize() const;
    virtual size_t EBOsize() const;
    virtual size_t VBOdata(void *vertexBuffer) const;
    virtual size_t EBOdata(void *elementBuffer, Index offset) const;
};

#endif // __MODEL_H__
