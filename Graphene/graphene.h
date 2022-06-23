#ifndef __GRAPHENE_H__
#define __GRAPHENE_H__

#define GLM_ENABLE_EXPERIMENTAL
#define GLM_FORCE_RADIANS

#include <GL/glew.h>
#include <GL/gl.h>

#include <SDL.h>

#include <string>
#include <vector>
#include <filesystem>
#include <map>
#include <array>
#include <memory>

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
    class Texture;
    class Material;
    class Object;
    class Model;
    class Camera;
    class Light;
    class SimpleObjects;
    class Scene;

    enum ShaderType
    {
        GeometryShader,
        VertexShader,
        TesselationControlShader,
        TesselationEvaluationShader,
        FragmentShader,
        ComputeShader,
        Invalid
    };
    
    enum BufferType
    {
        VertexBuffer = 0,
        ElementBuffer,
        StorageBuffer,
        UniformBuffer,
        BufferTypeMax
    };

    enum CameraType
    {
        Free = 0,
        Targeted
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
        fvec2 UV;
        uint meshId = 0;
        inline bool operator==(const struct Vertex &that)
        {
            return position == that.position
                && normal == that.normal
                && color == that.color
                && UV == that.UV
                && meshId == that.meshId;
        }
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

    typedef struct CameraMatrices
    {
    public:
        fmat4 world;
        fmat4 view;
        fmat4 projection;
        fvec3 position;
    private:
        char padding0[sizeof(float)] = { 0 };
    } CameraMatrices;

    typedef struct ModelMatrices
    {
        fmat4 model;
    } ModelMatrices;

protected:
    bool m_Started;
    bool m_Wireframe = false;
    
    std::shared_ptr<Scene> m_Scene;
    fvec3 m_ClearColor;

    void *m_VertexBuffer = nullptr;
    void *m_ElementBuffer = nullptr;
    void *m_StorageBuffer = nullptr;
    void *m_UniformBuffer = nullptr;
    size_t m_VertexBufferSize = 0;
    size_t m_ElementBufferSize = 0;
    size_t m_StorageBufferSize = 0;
    size_t m_UniformBufferSize = 0;
    
    unsigned int m_VAO;
    unsigned int m_Buffers[BufferTypeMax];
    
public:
    Graphene();
    Graphene(const Graphene &) = delete;
    Graphene(Graphene &&) = default;
    virtual ~Graphene();
    Graphene &operator=(const Graphene &) = delete;
    Graphene &operator=(Graphene &&) = default;
    virtual int draw();
    virtual std::shared_ptr<Graphene::Scene> scene() const;
    virtual void camera(std::shared_ptr<Graphene::Camera> camera);
    virtual void addModel(const Graphene::Model &model);
    virtual void addLight(const Graphene::Light &light);
    virtual void setClearColor(const Color &color);
    virtual void clear() const;
    virtual bool cull() const;
    virtual void cull(const bool enable);
    virtual bool gammaCorrection() const;
    virtual void gammaCorrection(const bool enable);
    virtual bool wireframe() const;
    virtual void wireframe(const bool enable);

protected:
    virtual size_t reAllocateVertexBuffer();
    virtual size_t reAllocateElementBuffer();
    virtual size_t reAllocateStorageBuffer();
    virtual size_t reAllocateUniformBuffer();
    virtual void fillVertexBuffer();
    virtual void fillElementBuffer();
    virtual void fillStorageBuffer();
    virtual void fillUniformBuffer();
    virtual void useMaterials();
    virtual void onGeometryChanged();
    virtual void onCameraChanged();
    virtual void onLightChanged();
    virtual void onEnvironmentChanged();
    virtual void onShaderChanged();
};

#include "shader.h"
#include "program.h"

#include "material.h"
#include "blinn.h"

#include "object.h"
#include "model.h"
#include "simpleobjects.h"

#include "camera.h"

#include "light.h"

#include "scene.h"

#endif // __GRAPHENE_H__
