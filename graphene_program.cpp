#include "graphene.h"

/*******************************************************************************
 * 
 * Graphene::Program
 * 
 ******************************************************************************/

Graphene::Program::Program()
{
    m_Handle = glCreateProgram();
}

Graphene::Program::~Program()
{
    glDeleteProgram(m_Handle);
}

GLuint Graphene::Program::handle() const
{
    return m_Handle;
}

void Graphene::Program::addShader(Shader &shader)
{
    m_Shaders.push_back(std::move(shader));
    glAttachShader(m_Handle, m_Shaders.back().handle());
}

int Graphene::Program::link()
{
    //std::for_each(m_Shaders.begin(), m_Shaders.end(), [](auto &s){ s.compiled() || s.compile(); });
    glLinkProgram(m_Handle);
    GLint logLen;
    glGetProgramiv(m_Handle, GL_INFO_LOG_LENGTH, &logLen);
    if (logLen)
    {
        m_Log.clear();
        m_Log.reserve(logLen);
        glGetProgramInfoLog(m_Handle, m_Log.capacity(), nullptr, m_Log.data());
        return -1;
    }
    else
        return 0;
}

bool Graphene::Program::linked() const
{
    GLint rv;
    glGetProgramiv(m_Handle, GL_LINK_STATUS, &rv);
    return rv;
}

bool Graphene::Program::deleted() const
{
    GLint rv;
    glGetProgramiv(m_Handle, GL_DELETE_STATUS, &rv);
    return rv;
}

bool Graphene::Program::valid() const
{
    GLint rv;
    glGetProgramiv(m_Handle, GL_VALIDATE_STATUS, &rv);
    return rv;
}

GLuint Graphene::Program::shaders() const
{
    GLint rv;
    glGetProgramiv(m_Handle, GL_ATTACHED_SHADERS, &rv);
    return rv;   
}

GLuint Graphene::Program::attributes() const
{
    GLint rv;
    glGetProgramiv(m_Handle, GL_ACTIVE_ATTRIBUTES, &rv);
    return rv;   
}

GLuint Graphene::Program::uniforms() const
{
    GLint rv;
    glGetProgramiv(m_Handle, GL_ACTIVE_UNIFORMS, &rv);
    return rv;       
}

const char *Graphene::Program::log() const
{
    return m_Log.c_str();
}
