#include "graphene.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <algorithm>

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

void Graphene::run()
{
    clear();
    glUseProgram(m_Program->handle());
}

Graphene::Program *const Graphene::program() const
{
    return m_Program;
}

void Graphene::clear() const
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

/*******************************************************************************
 * 
 * Graphene::Shader
 * 
 ******************************************************************************/

Graphene::Shader::Shader(Type type): m_Handle(0)
{
    m_Handle = glCreateShader(shaderType(type));
}

Graphene::Shader::~Shader()
{
    glDeleteShader(m_Handle);
}

int Graphene::Shader::load(std::filesystem::path &path)
{
    FILE *shaderSourceFile = fopen(path.c_str(), "rb");
    if (!shaderSourceFile)
    {
        m_LastError = errno;
        return -1;
    }
    struct stat shaderSourceFileStat;
    if (fstat(fileno(shaderSourceFile), &shaderSourceFileStat))
    {
        m_LastError = errno;
        fclose(shaderSourceFile);
        return -1;
    }
    size_t shaderSourceFileSize = shaderSourceFileStat.st_size;
    char *shaderSource = static_cast<char *>(malloc(shaderSourceFileSize + 1));
    shaderSource[shaderSourceFileSize] = 0;
    if (fread(shaderSource, shaderSourceFileSize, 1, shaderSourceFile) != 1)
    {
        m_LastError = errno;
        free(shaderSource);
        fclose(shaderSourceFile);
        return -1;
    }
    fclose(shaderSourceFile);
    glShaderSource(m_Handle, 1, &shaderSource, nullptr);
    return 0;
}

void Graphene::Shader::setSource(const std::string shaderSource)
{
    const char *shaderSourceString = shaderSource.data();
    glShaderSource(m_Handle, 1, &shaderSourceString, nullptr);
}

int Graphene::Shader::compile()
{
    glCompileShader(m_Handle);
    GLint logLen;
    glGetShaderiv(m_Handle, GL_INFO_LOG_LENGTH, &logLen);
    if (logLen)
    {
        m_Log.clear();
        m_Log.reserve(logLen);
        glGetShaderInfoLog(m_Handle, m_Log.capacity(), nullptr, m_Log.data());
        return -1;
    }
    else
    {
        m_Compiled = true;
        return 0;
    }
}

bool Graphene::Shader::compiled() const
{
    return m_Compiled;
}

GLuint Graphene::Shader::handle() const
{
    return m_Handle;
}


GLuint Graphene::Shader::shaderType(Type type) const
{
    constexpr GLuint map[6] = {
        GL_GEOMETRY_SHADER,
        GL_VERTEX_SHADER,
        GL_TESS_CONTROL_SHADER,
        GL_TESS_EVALUATION_SHADER,
        GL_FRAGMENT_SHADER,
        GL_COMPUTE_SHADER
    };
    return map[type];   
}

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
    {
        m_Linked = true;
        return 0;
    }
}

bool Graphene::Program::linked() const
{
    return m_Linked;
}

