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
        Ambient = 0,
        Diffuse,
        Specular
    };

public:
    Blinn();
    virtual ~Blinn() = default;
    virtual void use();
    virtual void setTexture(const TextureChannel &channel, std::shared_ptr<Texture> texture);

protected:
    std::shared_ptr<Texture> m_Ambient  = Graphene::Texture::FlatWhite();
    std::shared_ptr<Texture> m_Diffuse  = Graphene::Texture::FlatGray();
    std::shared_ptr<Texture> m_Specular = Graphene::Texture::FlatWhite();
};

#endif // __BLINN_H__
