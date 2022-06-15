#include "graphene.h"

void Graphene::Material::addShader(Shader &shader)
{
    m_Program.addShader(shader);
}

