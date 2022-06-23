#ifndef __BLINN_H__
#define __BLINN_H__

/*******************************************************************************
 *
 * Graphene::Material
 *
 ******************************************************************************/

#include <memory>
#include "texture.h"

class Graphene::Material::Blinn : public Graphene::Material
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
    void setTexture(TextureChannel &channel, std::shared_ptr<Texture> texture);

protected:
    std::shared_ptr<Texture> m_Ambient;
    std::shared_ptr<Texture> m_Diffuse;
    std::shared_ptr<Texture> m_Specular;
    std::shared_ptr<Texture> m_Bump;
};

#endif // __BLINN_H__
