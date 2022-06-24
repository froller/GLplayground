#include "graphene.h"

void Graphene::Material::setTexture(std::shared_ptr<Texture> texture)
{
    m_Texture = texture;
}

void Graphene::Material::useTextures()
{
    m_Texture->use();
}

void Graphene::Material::addShader(Shader &shader)
{
    m_Program.addShader(shader);
}

