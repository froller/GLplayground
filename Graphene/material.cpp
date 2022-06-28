#include "graphene.h"

void Graphene::Material::addShader(std::shared_ptr<Shader> shader)
{
    m_Program.addShader(shader);
}

Graphene::Material::Default::Default()
{
    std::shared_ptr<Shader> vertexShader = std::make_shared<Shader>(ShaderType::Vertex);
    vertexShader->loadSource(std::filesystem::path("../Shaders/default.vertex.glsl"));
    std::shared_ptr<Shader> fragmentShader = std::make_shared<Shader>(ShaderType::Fragment);
    fragmentShader->loadSource(std::filesystem::path("../Shaders/default.fragment.glsl"));
    m_Program.addShader(vertexShader);
    m_Program.addShader(fragmentShader);
}

Graphene::Material::Default::~Default()
{

}
