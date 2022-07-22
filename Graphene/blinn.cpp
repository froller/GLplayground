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

void Graphene::Material::Blinn::use()
{
    Material::use();
/*
    if (m_Ambient)
    {
        glBindTexture(GL_TEXTURE_2D, m_Ambient->textureID());
        glBindTextureUnit(GL_TEXTURE0, m_Ambient->textureID());
    }
*/
    if (m_Diffuse)
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_Diffuse->textureID());
        //glBindTextureUnit(GL_TEXTURE0, m_Diffuse->textureID());
    }
    if (m_Specular)
    {
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, m_Specular->textureID());
        //glBindTextureUnit(GL_TEXTURE1, m_Specular->textureID());
    }
/*
    if (m_Bump)
    {
        glBindTexture(GL_TEXTURE_2D, m_Bump->textureID());
        glActiveTexture(GL_TEXTURE0);
    }
*/
}

void Graphene::Material::Blinn::setTexture(const TextureChannel &channel, std::shared_ptr<Texture> texture)
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
