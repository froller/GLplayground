#include "bumped.h"

Graphene::Material::Bumped::Bumped()
{
    std::shared_ptr<Shader> fragmentShader = m_Program.getShader(ShaderType::Fragment);
    m_Program.removeShader(fragmentShader);
    fragmentShader = std::make_shared<Shader>(ShaderType::Fragment);
    fragmentShader->loadSource(std::filesystem::path("../Shaders/bumped.fragment.glsl"));
    m_Program.addShader(fragmentShader);
}

void Graphene::Material::Bumped::use()
{
    Blinn::use();
    
    if (m_Bump)
    {
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, m_Bump->textureID());
    }
}

void Graphene::Material::Bumped::setTexture(const TextureChannel &channel, std::shared_ptr<Texture> texture)
{
    switch (channel)
    {
    case (TextureChannel::Ambient):
        m_Ambient = texture;
        break;
    case (TextureChannel::Diffuse):
        m_Diffuse = texture;
        break;
    case (TextureChannel::Specular):
        m_Specular = texture;
        break;
    case (TextureChannel::Bump):
        m_Bump = texture;
        break;
    default:
        SDL_LogError(SDL_LOG_CATEGORY_RENDER, "Unknown texture channel %u", channel);
    }
}
