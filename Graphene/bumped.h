#ifndef __BUMPED_H__
#define __BUMPED_H__


#include "graphene.h"

class Graphene::Material::Bumped : public Graphene::Material::Blinn
{
public:
    enum class TextureChannel {
        Ambient = 0,
        Diffuse,
        Specular,
        Bump
    };

public:
    Bumped();
    virtual ~Bumped() = default;
    virtual void use();
    virtual void setTexture(const TextureChannel &channel, std::shared_ptr<Texture> texture);
  
protected:
    std::shared_ptr<Texture> m_Bump  = Graphene::Texture::FlatGray();

};

#endif // __BUMPED_H__
