#ifndef __GRAPHENE_H__
#define __GRAPHENE_H__

#define GLM_ENABLE_EXPERIMENTAL
#include <GL/glew.h>
#include <GL/gl.h>

#include <SDL2/SDL.h>

#include <string>
#include <vector>
#include <filesystem>
#include <map>
#include <array>

#include "graphene_types.h"

class Graphene
{
public:
    class Shader;
    class Program;
    class Object;
    class Model;
    class Camera;
    class SimpleObjects;
    class Scene;
    
protected:
    Program *m_Program;
    Scene *m_Scene;
    
public:
    Graphene();
    Graphene(const Graphene &) = delete;
    Graphene(Graphene &&) = default;
    virtual ~Graphene();
    Graphene &operator=(const Graphene &) = delete;
    Graphene &operator=(Graphene &&) = default;
    virtual int run();
    virtual int addShader(const ShaderType type, const std::string &source);
    virtual int addShader(const ShaderType type, const std::filesystem::path &path);
    virtual Scene *scene() const;
protected:
    virtual void clear() const;
};

class Graphene::Shader
{    
protected:
    GLuint m_Handle;
    std::string m_Log;
    uint64_t m_LastError;

public:
    Shader(ShaderType type);
    Shader(const Shader &) = delete;
    Shader(Shader &&) = default;
    virtual ~Shader();
    Shader &operator=(const Shader &) = delete;
    Shader &operator=(Shader &&) = default;
    virtual int loadSource(const std::filesystem::path &path);
    virtual void setSource(const std::string &shader);
    virtual int compile();
    virtual bool compiled() const;
    virtual bool deleted() const;
    virtual bool type() const;
    virtual const GLuint shaderType(const ShaderType type) const;
    virtual const ShaderType shaderType(const GLuint type) const;
    virtual GLuint handle() const;
    virtual const char *log() const;
};

class Graphene::Program
{
protected:
    GLuint m_Handle;
    std::vector<Shader> m_Shaders;
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
    virtual int use();
    virtual bool linked() const;
    virtual bool deleted() const;
    virtual bool valid() const;
    virtual GLuint shaders() const;
    virtual GLuint attributes() const;
    virtual GLuint uniforms() const;
    virtual const char* log() const;
};

class Graphene::Object
{
public:
    fvec3 m_Position;
    fvec3 m_Rotation;
    fvec3 m_Scale;
    
public:
    Object() = default;
    virtual ~Object() = default;
};

class Graphene::Model : public Graphene::Object
{
public:
    std::vector<fvec3> m_Vertices;
    std::vector<fvec3> m_Attributes;
    std::vector<std::array<unsigned int, 3>> m_Primitives;
public:
    Model() = default;
    virtual ~Model() = default;
    //virtual load(cont std::filesystem::path &path);
    virtual void addPrimitive(const fvec3 a, const fvec3 b, const fvec3 c);
    virtual void addPrimitive(const std::array<fvec3, 3> vertices);
    virtual const size_t vertexCount() const;
    virtual const size_t VBOsize() const;
    virtual const void *VBO() const;
    virtual const size_t EBOsize() const;
    virtual const void *EBO() const;
};

class Graphene::Camera : public Graphene::Object
{
public:
    class Free;
    class Targeted;
public:
    float m_AspectRatio;
    float m_FOV;
public:
    Camera() = default;
    virtual ~Camera() = default;
    virtual const fmat4 view() const = 0;
    virtual const fmat4 projection() const;
};

#include "camera.h"

class Graphene::SimpleObjects
{
public:
    class Triangle;
    class Square;
    class Tetrahedron;
    class Cube;
    class Sphere;
};

#include "simpleobjects.h"

class Graphene::Scene
{
protected:
    std::vector<Graphene::Model> m_Models;
    Graphene::Camera *m_DefaultCamera;
    Graphene::Camera *m_Camera;
public:
    Scene();
    virtual ~Scene();
    virtual void resetCamera();
    virtual void setCamera(Graphene::Camera *camera);
    virtual void addModel(const Graphene::Model &model);
    virtual const unsigned int vertexCount() const;
    virtual const uint64_t VBOsize() const;
    virtual const void *VBO() const;
    virtual const uint64_t EBOsize() const;
    virtual const void *EBO() const;
};

#endif // __GRAPHENE_H__
