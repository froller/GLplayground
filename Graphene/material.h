#ifndef __MATERIAL_H__
#define __MATERIAL_H__

/*******************************************************************************
 *
 * Graphene::Material
 *
 ******************************************************************************/

class Graphene::Material
{
public:
    class Blinn;

public:
    Graphene::Program m_Program;
    std::shared_ptr<Graphene::Texture> m_Texture;

public:
    Material(): m_Program(), m_Texture(nullptr) {};
    Material(const Material &) = delete;
    Material(Material &&) = default;
    virtual ~Material() = default;
    Material &operator=(const Material &) = delete;
    Material &operator=(Material &&) = default;
    virtual void setTexture(std::shared_ptr<Texture> texture);
    virtual void useTextures();


public:
    virtual void addShader(Shader &shader);
};

#endif // __MATERIAL_H__