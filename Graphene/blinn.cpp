#include "graphene.h"

Graphene::Material::Blinn::Blinn() : m_Ambient(nullptr), m_Diffuse(nullptr), m_Specular(nullptr), m_Bump(nullptr)
{
}

void Graphene::Material::Blinn::setTexture(Graphene::Material::Blinn::TextureChannel &channel, std::shared_ptr<Texture> texture)
{
    switch (channel)
    {
    case(Graphene::Material::Blinn::TextureChannel::Ambient):
        m_Ambient = texture;
        break;
    case(Graphene::Material::Blinn::TextureChannel::Diffuse):
        m_Diffuse = texture;
        break;
    case (Graphene::Material::Blinn::TextureChannel::Specular):
        m_Specular = texture;
        break;
    case (Graphene::Material::Blinn::TextureChannel::Bump):
        m_Bump = texture;
        break;
    default:
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Unknown texture channel %u", channel);
    }
}
