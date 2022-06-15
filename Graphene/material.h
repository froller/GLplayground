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
    Graphene::Program m_Program;

public:
    Material(): m_Program() {};
    Material(const Material &) = delete;
    Material(Material &&) = default;
    virtual ~Material() = default;
    Material &operator=(const Material &) = delete;
    Material &operator=(Material &&) = default;

public:
    virtual void addShader(Shader &shader);
};

#endif // __MATERIAL_H__