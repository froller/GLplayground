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

void Graphene::Program::addShader(const std::shared_ptr<Shader> &shader)
{
    shader->compile();
    glAttachShader(m_Handle, shader->handle());
    m_Shaders.push_back(shader);
    SDL_LogDebug(SDL_LOG_CATEGORY_RENDER, "Shader %u added to program %u", shader->handle(), m_Handle);
}

void Graphene::Program::removeShader(const std::shared_ptr<Shader>& shader)
{
    m_Shaders.remove(shader);
    glDetachShader(m_Handle, shader->handle());
    SDL_LogDebug(SDL_LOG_CATEGORY_RENDER, "Shader %u removed from program %u", shader->handle(), m_Handle);
}

std::shared_ptr<Graphene::Shader> Graphene::Program::getShader(const ShaderType &type)
{
    for (auto shader = m_Shaders.begin(); shader != m_Shaders.end(); ++shader)
        if ((*shader)->type() == type)
            return (*shader);
    return nullptr;
}

int Graphene::Program::use()
{
    if (!linked())
        if (link())
            return -1;
    glUseProgram(m_Handle);
    return 0;
}

int Graphene::Program::link()
{
    for (auto shader = m_Shaders.begin(); shader != m_Shaders.end(); ++shader)
        if (!(*shader)->compiled())
            return -1;
    glLinkProgram(m_Handle);
    if (!linked())
    {
        GLint logLen;
        glGetProgramiv(m_Handle, GL_INFO_LOG_LENGTH, &logLen);
        m_Log.clear();
        m_Log.reserve(logLen);
        glGetProgramInfoLog(m_Handle, m_Log.capacity(), nullptr, m_Log.data());
        SDL_LogCritical(SDL_LOG_CATEGORY_RENDER, "Error linking program: %s\n", m_Log.c_str());
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

int Graphene::Program::shaders() const
{
    GLint rv;
    glGetProgramiv(m_Handle, GL_ATTACHED_SHADERS, &rv);
    return rv;
}

int Graphene::Program::attributes() const
{
    GLint rv;
    glGetProgramiv(m_Handle, GL_ACTIVE_ATTRIBUTES, &rv);
    return rv;
}

int Graphene::Program::uniforms() const
{
    GLint rv;
    glGetProgramiv(m_Handle, GL_ACTIVE_UNIFORMS, &rv);
    return rv;
}

int Graphene::Program::uniformMaxLen() const
{
    GLint rv;
    glGetProgramiv(m_Handle, GL_ACTIVE_UNIFORM_MAX_LENGTH, &rv);
    return rv;
}

unsigned int Graphene::Program::uniformIndex(const char *name) const
{
    return glGetUniformLocation(m_Handle, name);
}

char *Graphene::Program::uniformName(const unsigned int index) const
{
    constexpr size_t rvCapacity = 256;
    char *rv = new char[rvCapacity];
    int rvSize;
    glGetActiveUniform(m_Handle, index, rvCapacity, &rvSize, nullptr, nullptr, rv);
    return rv;
}

unsigned int Graphene::Program::uniformType(const unsigned int index) const
{
    unsigned int rv;
    glGetActiveUniform(m_Handle, index, 0, nullptr, nullptr, &rv, nullptr);
    return rv;
}

int Graphene::Program::uniformSize(const unsigned int index) const
{
    int rv;
    glGetActiveUniform(m_Handle, index, 0, nullptr, &rv, nullptr, nullptr);
    return rv;
}

int Graphene::Program::setUniformBuffer(const unsigned int /*index*/, void */*buffer*/) const
{
    return 0;
}

int Graphene::Program::setUniformBuffer(const char *name, void *buffer) const
{
    //const int index = glGetUniformBlockIndex(m_Handle, name);
    const int index = glGetUniformBlockIndex(m_Handle, name);
    if (index < 0)
        return index;
    setUniformBuffer(index, buffer);
    return 0;
}

template<>
void Graphene::Program::setUniform<int>(const unsigned int index, int value) const
{
    glUniform1i(index, value);
}

template<>
void Graphene::Program::setUniform<unsigned int>(const unsigned int index, unsigned int value) const
{
    glUniform1ui(index, value);
}

template<>
void Graphene::Program::setUniform<float>(const unsigned int index, float value) const
{
    glUniform1f(index, value);
}

template<>
void Graphene::Program::setUniform<double>(const unsigned int index, double value) const
{
    glUniform1d(index, value);
}

template<>
void Graphene::Program::setUniform<fvec3>(const unsigned int index, fvec3 value) const
{
    glUniform3fv(index, 1, (float *)&value);
}

template<>
void Graphene::Program::setUniform<fmat4>(const unsigned int index, fmat4 value) const
{
    glUniformMatrix4fv(index, 1, false, (float *)&value);
}

const char *Graphene::Program::log() const
{
    return m_Log.c_str();
}
