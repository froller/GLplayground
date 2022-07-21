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
    virtual Material &operator=(const Material &) = delete;
    virtual Material &operator=(Material &&) = default;
    virtual void use();

public:
    virtual void addShader(std::shared_ptr<Shader> shader) final;
    //    virtual void setTexture(std::shared_ptr<Texture> texture);
    //    virtual void useTextures();
};

class Graphene::Material::Default : public Material
{
public:
    Default();
    virtual ~Default();
};

#endif // __MATERIAL_H__