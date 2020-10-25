#include "graphene.h"

#include <string.h>

/*******************************************************************************
 * 
 * Graphene
 * 
 ******************************************************************************/

Graphene::Graphene()
{
    m_Program = new Program();
}

Graphene::~Graphene()
{
    delete m_Program;
}

int Graphene::run()
{
    if (!m_Program->linked())
    {
        if (m_Program->link())
            return -1;
    }
    clear();
    glUseProgram(m_Program->handle());
    return 0;
}

int Graphene::addShader(const ShaderType type, const std::string &source)
{
    Shader shader(type);
    shader.setSource(source);
    m_Program->addShader(shader);
    return 0;
}

int Graphene::addShader(const ShaderType type, const std::filesystem::path &path)
{
    Shader shader(type);
    GLuint rv = shader.loadSource(path);
    if (!rv)
        m_Program->addShader(shader);
    return rv;
}

void Graphene::clear() const
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
