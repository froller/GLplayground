#ifndef __GRAPHENE_H__
#define __GRAPHENE_H__

#define GLM_ENABLE_EXPERIMENTAL
#include <GL/glew.h>
#include <GL/gl.h>

#include <SDL.h>

#include <string>
#include <vector>
#include <filesystem>
#include <map>
#include <array>

#include <math.h>
#ifdef _WIN32
#   define M_PI_2 M_PI / 2.f
#   define M_PI_4 M_PI / 4.f
#   define M_2_PI M_PI * 2.f
#endif

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
    
    enum BufferType {
        VertexBuffer = 0,
        ElementBuffer,
        LightBuffer,
        BufferTypeMax
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

    typedef struct LightSource
    {
    public:
        fvec3 position;
    private:
        char padding0[sizeof(float)] = { 0 };
    public:
        Color color;
        float attenuation;
    } LightSource;
    
protected:
    bool m_Started;
    
    Program *m_Program;
    Scene *m_Scene;
    fvec3 m_ClearColor;

    void *m_VertexBuffer = nullptr;
    void *m_ElementBuffer = nullptr;
    void *m_LightBuffer = nullptr;
    size_t m_VertexBufferSize = 0;
    size_t m_ElementBufferSize = 0;
    size_t m_LightBufferSize = 0;
    
    unsigned int m_VAO;
    unsigned int m_Buffers[BufferTypeMax];
    
public:
    Graphene();
    Graphene(const Graphene &) = delete;
    Graphene(Graphene &&) = default;
    virtual ~Graphene();
    Graphene &operator=(const Graphene &) = delete;
    Graphene &operator=(Graphene &&) = default;
    virtual int start();
    virtual int draw();
    virtual void stop();
    virtual Graphene::Scene *scene() const;
    virtual int addShader(const ShaderType type, const std::string &source);
    virtual int addShader(const ShaderType type, const std::filesystem::path &path);
    virtual void camera(Graphene::Camera *camera);
    virtual void addModel(const Graphene::Model &model);
    virtual void addLight(const Graphene::Light &light);
    virtual void setClearColor(const Color color);
    virtual void clear() const;

protected:
    virtual size_t reAllocateVertexBuffer();
    virtual size_t reAllocateElementBuffer();
    virtual size_t reAllocateLightBuffer();
    virtual void fillVertexBuffer();
    virtual void fillElementBuffer();
    virtual void fillLightBuffer();
    virtual void onGeometryChanged();
    virtual void onCameraChanged();
    virtual void onLightChanged();
    virtual void onEnvironmentChanged();
};

#include "shader.h"
#include "program.h"

#include "object.h"
#include "model.h"
#include "simpleobjects.h"

#include "camera.h"

#include "light.h"

#include "scene.h"

#endif // __GRAPHENE_H__
