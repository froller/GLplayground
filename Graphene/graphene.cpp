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
    m_Scene = new Scene();
}

Graphene::~Graphene()
{
    delete m_Program;
}

int Graphene::run()
{
    if (!m_Program->linked())
        if (m_Program->link())
            return -1;
    clear();
    
    GLuint bufferHandles[2];
    glCreateBuffers(2, bufferHandles);
    glBindBuffer(GL_ARRAY_BUFFER, bufferHandles[0]);
    glBufferData(GL_ARRAY_BUFFER, m_Scene->VBOsize(), m_Scene->VBO(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferHandles[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Scene->EBOsize(), m_Scene->EBO(), GL_STATIC_DRAW);
    
    glDrawArrays(GL_TRIANGLES, 0, m_Scene->vertexCount());
    
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
    if (shader.loadSource(path))
    {
        SDL_LogCritical(SDL_LOG_CATEGORY_VIDEO, "Error loading shader source: %s\n", shader.log());
        return -1;
    }
    m_Program->addShader(shader);
    return 0;
}

Graphene::Scene * Graphene::scene() const
{
    return m_Scene;
}


void Graphene::clear() const
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
