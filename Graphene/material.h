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
    class Default;
    class Blinn;

public:
    Graphene::Program m_Program;

public:
    Material(): m_Program() {};
    Material(const Material &) = delete;
    Material(Material &&) = default;
    virtual ~Material() = default;
    Material &operator=(const Material &) = delete;
    Material &operator=(Material &&) = default;

public:
    virtual void addShader(std::shared_ptr<Shader> shader) final;
    //    virtual void setTexture(std::shared_ptr<Texture> texture);
    //    virtual void useTextures();
};

class Graphene::Material::Default : public Material
{
public:
    std::shared_ptr<Texture> m_Texture;

public:
    Default();
    virtual ~Default();

};

#endif // __MATERIAL_H__