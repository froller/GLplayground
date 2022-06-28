#include "graphene.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

/*******************************************************************************
 * 
 * Graphene::Shader
 * 
 ******************************************************************************/

Graphene::Shader::Shader(const ShaderType type)
{
    m_Handle = glCreateShader(shaderType(type));
}

Graphene::Shader::~Shader()
{
    glDeleteShader(m_Handle);
}

int Graphene::Shader::loadSource(const std::filesystem::path &path)
{
    FILE *shaderSourceFile = fopen(path.string().c_str(), "rb");
    if (!shaderSourceFile)
    {
        m_LastError = errno;
        m_Log = strerror(m_LastError);
        return -1;
    }
    struct stat shaderSourceFileStat;
    if (fstat(_fileno(shaderSourceFile), &shaderSourceFileStat))
    {
        m_LastError = errno;
        m_Log = strerror(m_LastError);
        fclose(shaderSourceFile);
        return -1;
    }
    size_t shaderSourceFileSize = shaderSourceFileStat.st_size;
    char *shaderSource = static_cast<char *>(malloc(shaderSourceFileSize + 1));
    shaderSource[shaderSourceFileSize] = 0;
    if (fread(shaderSource, shaderSourceFileSize, 1, shaderSourceFile) != 1)
    {
        m_LastError = errno;
        m_Log = strerror(m_LastError);
        free(shaderSource);
        fclose(shaderSourceFile);
        return -1;
    }
    fclose(shaderSourceFile);
    glShaderSource(m_Handle, 1, const_cast<const char **>(&shaderSource), nullptr);
    return 0;
}

void Graphene::Shader::setSource(const std::string &shaderSource)
{
    const char *shaderSourceString = shaderSource.data();
    glShaderSource(m_Handle, 1, &shaderSourceString, nullptr);
}

int Graphene::Shader::compile()
{
    glCompileShader(m_Handle);
    if (!compiled())
    {
        GLint logLen;
        glGetShaderiv(m_Handle, GL_INFO_LOG_LENGTH, &logLen);
        m_Log.clear();
        m_Log.reserve(logLen);
        glGetShaderInfoLog(m_Handle, m_Log.capacity(), nullptr, m_Log.data());
        SDL_LogCritical(SDL_LOG_CATEGORY_VIDEO, "Error compiling shader: %s\n", m_Log.c_str());
        return -1;
    }
    else
        return 0;
}

bool Graphene::Shader::compiled() const
{
    GLint rv;
    glGetShaderiv(m_Handle, GL_COMPILE_STATUS, &rv);
    return rv;
}

bool Graphene::Shader::deleted() const
{
    GLint rv;
    glGetShaderiv(m_Handle, GL_DELETE_STATUS, &rv);
    return rv;
}

Graphene::ShaderType Graphene::Shader::type() const
{
    GLint rv;
    glGetShaderiv(m_Handle, GL_SHADER_TYPE, &rv);
    return shaderType(static_cast<GLuint>(rv));
}

GLuint Graphene::Shader::handle() const
{
    return m_Handle;
}

const GLuint Graphene::Shader::shaderType(const ShaderType type) const
{
    constexpr GLuint map[] = {
        GL_GEOMETRY_SHADER,
        GL_VERTEX_SHADER,
        GL_TESS_CONTROL_SHADER,
        GL_TESS_EVALUATION_SHADER,
        GL_FRAGMENT_SHADER,
        GL_COMPUTE_SHADER,
        GL_INVALID_ENUM
    };
    return map[size_t(type)];
}

const enum Graphene::ShaderType Graphene::Shader::shaderType(const GLuint type) const
{
    const std::map<const GLuint, const ShaderType> map = {
        {GL_GEOMETRY_SHADER, ShaderType::Geometry},
        {GL_VERTEX_SHADER, ShaderType::Vertex},
        {GL_TESS_CONTROL_SHADER, ShaderType::TesselationControl},
        {GL_TESS_EVALUATION_SHADER, ShaderType::TesselationEvaluation},
        {GL_FRAGMENT_SHADER, ShaderType::Fragment},
        {GL_COMPUTE_SHADER, ShaderType::Compute},
        {GL_INVALID_ENUM, ShaderType::Invalid}
    };
    return map.at(type);
}

const char *Graphene::Shader::log() const
{
    return m_Log.c_str();
}
