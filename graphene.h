#ifndef __OPENGL_H__
#define __OPENGL_H__

#include <string>
#include <vector>
#include <filesystem>

# define GLM_ENABLE_EXPERIMENTAL

# include <GL/glew.h>
# include <GL/gl.h>
//# include <SDL.h>

class Graphene
{
public:
    class Shader;
    class Program;

protected:
    Program *m_Program;
    
public:
    Graphene();
    Graphene(const Graphene &) = delete;
    Graphene(Graphene &&) = default;
    virtual ~Graphene();
    Graphene &operator=(const Graphene &) = delete;
    Graphene &operator=(Graphene &&) = default;
    virtual void run();
    virtual Program *const program() const;
protected:
    virtual void clear() const;
    
};

class Graphene::Shader
{
public:
    enum Type {
        Geometry,
        Vertex,
        TesselationControl,
        TesselationEvaluation,
        Fragment,
        Compute
    };
    
protected:
    GLuint m_Handle;
    bool m_Compiled;
    std::string m_Log;
    uint64_t m_LastError;

public:
    Shader(Type type);
    Shader(const Shader &) = delete;
    Shader(Shader &&) = default;
    virtual ~Shader();
    Shader &operator=(const Shader &) = delete;
    Shader &operator=(Shader &&) = default;
    virtual int load(std::filesystem::path &path);
    virtual void setSource(const std::string shaderSource);
    virtual int compile();
    virtual bool compiled() const;
    virtual GLuint shaderType(Type type) const;
    virtual GLuint handle() const;
};

class Graphene::Program
{
protected:
    GLuint m_Handle;
    std::vector<Shader> m_Shaders;
    bool m_Linked;
    std::string m_Log;
    uint64_t m_LastError;

public:
    Program();
    Program(const Program &) = delete;
    virtual ~Program();
    Program &operator=(const Program &) = delete;
    virtual GLuint handle() const;
    virtual void addShader(Shader &shader);
    virtual int link();
    virtual bool linked() const;
};

#endif // __OPENGL_H__
