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

/*******************************************************************************
 * 
 * Graphene
 * 
 ******************************************************************************/

class Graphene
{
public:
    class Shader;
    class Program;
    class Object;
    class Model;
    class Camera;
    class Light;
    class SimpleObjects;
    class Scene;

    enum ShaderType {
        GeometryShader,
        VertexShader,
        TesselationControlShader,
        TesselationEvaluationShader,
        FragmentShader,
        ComputeShader,
        Invalid
    };
    
    constexpr static unsigned int ElementSize = 3;
    
    typedef unsigned int Index;
    
    typedef std::array<Index, ElementSize> Element;
    
    typedef fvec3 Color;

    typedef struct Vertex
    {
        fvec3 position;
        fvec3 normal;
        Color color;       
        inline bool operator==(const struct Vertex &that);
    } Vertex;
    
protected:
    Program *m_Program;
    Scene *m_Scene;
    fvec3 m_ClearColor;
    
public:
    Graphene();
    Graphene(const Graphene &) = delete;
    Graphene(Graphene &&) = default;
    virtual ~Graphene();
    Graphene &operator=(const Graphene &) = delete;
    Graphene &operator=(Graphene &&) = default;
    virtual int run();
    virtual Graphene::Scene *scene() const;
    virtual int addShader(const ShaderType type, const std::string &source);
    virtual int addShader(const ShaderType type, const std::filesystem::path &path);
    virtual void setCamera(Graphene::Camera *camera);
    virtual void addModel(const Graphene::Model &model);
    virtual void setClearColor(const Color color);
    virtual void clear() const;
};

/*******************************************************************************
 * 
 * Graphene::Shader
 * 
 ******************************************************************************/

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
    virtual GLuint handle() const;
    virtual int loadSource(const std::filesystem::path &path);
    virtual void setSource(const std::string &shader);
    virtual int compile();
    virtual bool compiled() const;
    virtual bool deleted() const;
    virtual int type() const;
    virtual const GLuint shaderType(const ShaderType type) const;
    virtual const ShaderType shaderType(const GLuint type) const;
    virtual const char *log() const;
};

/*******************************************************************************
 * 
 * Graphene::Program
 * 
 ******************************************************************************/

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
    virtual int shaders() const;
    virtual int attributes() const;
    virtual int uniforms() const;
    virtual int uniformMaxLen() const;
    virtual char *uniformName(const unsigned int index) const;
    virtual unsigned int uniformType(const unsigned int index) const;
    virtual int uniformSize(const unsigned int index) const;

    template<typename T>
    void setUniform(const unsigned int index, T value) const;
    
    template<typename T>
    int setUniform(const char *name, T value) const
    {
        const int index = glGetUniformLocation(m_Handle, name);
        if (index < 0)
            return index;
        setUniform(index, value);
        return 0;
    }
    
    virtual const char* log() const;
};

/*******************************************************************************
 * 
 * Graphene::Object
 * 
 ******************************************************************************/

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

/*******************************************************************************
 * 
 * Graphene::Model
 * 
 ******************************************************************************/

class Graphene::Model : public Graphene::Object
{
public:
    std::vector<Vertex> m_Vertices;
    std::vector<std::array<unsigned int, 3>> m_Primitives;
public:
    Model() = default;
    virtual ~Model() = default;
    //virtual load(cont std::filesystem::path &path);
    virtual void addPrimitive(const Vertex a, const Vertex b, const Vertex c);
    virtual void addPrimitive(const std::array<Vertex, 3> vertices);
    virtual size_t vertexCount() const;
    virtual size_t elementCount() const;
    virtual size_t VBOsize() const;
    virtual size_t EBOsize() const;
    virtual size_t VBOdata(void *vertexBuffer) const;
    virtual size_t EBOdata(void *elementBuffer, Index offset) const;
};

/*******************************************************************************
 * 
 * Graphene::Camera
 * 
 ******************************************************************************/

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
    virtual fmat4 view() const = 0;
    virtual fmat4 projection() const;
};

#include "camera.h"

/*******************************************************************************
 * 
 * Graphene::Light
 * 
 ******************************************************************************/

class Graphene::Light : public Graphene::Object
{
public:
    class Omni;
public:
    fvec3 m_Color;
public:
    Light() = default;
    virtual ~Light() = default;
    virtual fmat4 view() const = 0;
    virtual fmat4 projection() const = 0;
};

#include "light.h"

/*******************************************************************************
 * 
 * Graphene::SimpleObjects
 * 
 ******************************************************************************/

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

/*******************************************************************************
 * 
 * Graphene::Scene
 * 
 ******************************************************************************/

class Graphene::Scene
{
    friend Graphene; // FIXME это зло должно быть уничтожено
    // сейчас используется для получения доступа к m_Ambient
protected:
    enum BufferType {
        VertexBuffer = 0,
        ElementBuffer,
        BufferTypeMax
    };
protected:
    std::vector<Graphene::Model> m_Models;
    Graphene::Camera * const m_DefaultCamera;
    Graphene::Camera *m_Camera;
    Graphene::Color m_Ambient;
    
    unsigned int m_VAO;
    unsigned int m_Buffers[BufferTypeMax];
public:
    Scene();
    virtual ~Scene();
    virtual void resetCamera();
    virtual void setCamera(Graphene::Camera *camera);
    virtual void addModel(const Graphene::Model &model);
    virtual void setAmbient(const Graphene::Color color);
    virtual void draw() const;
    virtual size_t vertexCount() const;
    virtual size_t elementCount() const;
    virtual unsigned int VBO() const;
    virtual unsigned int EBO() const;
    virtual size_t VBOsize() const;
    virtual size_t EBOsize() const;
    virtual size_t VBOdata(void *vertexBuffer) const;
    virtual size_t EBOdata(void *elementBuffer) const;
    virtual Graphene::Camera *camera();
    virtual fmat4 model() const;
};

#endif // __GRAPHENE_H__
