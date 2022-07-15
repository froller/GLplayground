#ifndef __BLINN_H__
#define __BLINN_H__

/*******************************************************************************
 *
 * Graphene::Material
 *
 ******************************************************************************/

#include <memory>

class Graphene::Material::Blinn : public Material
{
public:
    enum class TextureChannel {
        Ambient,
        Diffuse,
        Specular,
        Bump
    };

public:
    Blinn();
    virtual ~Blinn() = default;
    void setTexture(const TextureChannel &channel, std::shared_ptr<Texture> texture);

protected:
    std::shared_ptr<Texture> m_Ambient;
    std::shared_ptr<Texture> m_Diffuse;
    std::shared_ptr<Texture> m_Specular;
    std::shared_ptr<Texture> m_Bump;
};

#endif // __BLINN_H__
