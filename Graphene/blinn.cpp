#include "graphene.h"

Graphene::Material::Blinn::Blinn() : m_Ambient(nullptr), m_Diffuse(nullptr), m_Specular(nullptr), m_Bump(nullptr)
{
    std::shared_ptr<Shader> vertexShader = std::make_shared<Shader>(ShaderType::Vertex);
    vertexShader->loadSource(std::filesystem::path("../Shaders/blinn.vertex.glsl"));
    std::shared_ptr<Shader> fragmentShader = std::make_shared<Shader>(ShaderType::Fragment);
    fragmentShader->loadSource(std::filesystem::path("../Shaders/blinn.fragment.glsl"));
    m_Program.addShader(vertexShader);
    m_Program.addShader(fragmentShader);
}

void Graphene::Material::Blinn::setTexture(const Graphene::Material::Blinn::TextureChannel &channel, std::shared_ptr<Texture> texture)
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
        SDL_LogError(SDL_LOG_CATEGORY_RENDER, "Unknown texture channel %u", channel);
    }
}
