#ifndef __GRAPHENE_H__
#define __GRAPHENE_H__

#define GLM_ENABLE_EXPERIMENTAL
#define GLM_FORCE_RADIANS

#include <GL/glew.h>
#include <GL/gl.h>

#if defined(__clang__) && defined(_WIN32)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmacro-redefined"
#pragma clang diagnostic ignored "-Wpragma-pack"
#endif // __clang__ && _WIN32
#include <SDL.h>
#if defined(__clang__) && defined(_WIN32)
#pragma clang diagnostic pop
#endif // __clang__ && _WIN32

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

    enum class ShaderType
    {
        Geometry,
        Vertex,
        TesselationControl,
        TesselationEvaluation,
        Fragment,
        Compute,
        Invalid
    };

    enum class BufferType
    {
        Vertex = 0,
        Element,
        Storage,
        Uniform,
        BufferTypeMax
    };

    constexpr static unsigned int ElementSize = 3;  // Количество вершин в элементе (треугольнике или полигоне)

    typedef std::array<GLsizei, ElementSize> Element;

    typedef fvec3 Color;

    typedef struct Vertex
    {
        fvec3 position;
        fvec3 normal;
        fvec2 UV;
        uint materialId = 0;
        uint meshId = 0;
        inline bool operator==(const struct Vertex &that)
        {
            return position == that.position
                && normal == that.normal
                && UV == that.UV
                && materialId == that.materialId
                && meshId == that.meshId;
        }
    } Vertex;

    typedef struct LightSource
    {
    public:
        fvec3 position;
    private:
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-private-field"
#endif // __clang__
        char padding0[sizeof(float)] = { 0 };
#if defined(__clang__)
#pragma clang diagnostic pop
#endif // __clang__
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
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-private-field"
#endif // __clang__
        char padding0[sizeof(float)] = { 0 };
#if defined(__clang__)
#pragma clang diagnostic pop
#endif // __clang__
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
    unsigned int m_Buffers[size_t(BufferType::BufferTypeMax)];
    
public:
    Graphene();
    Graphene(const Graphene &) = delete;
    Graphene(Graphene &&) = default;
    virtual ~Graphene();
    Graphene &operator=(const Graphene &) = delete;
    Graphene &operator=(Graphene &&) = default;
    virtual int drawScene();
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
    virtual size_t fillElementBuffer(std::shared_ptr<Material> material);
    virtual void fillStorageBuffer();
    virtual void fillUniformBuffer();
    virtual void useTextures();
    virtual void onGeometryChanged(std::shared_ptr<Material> material);
    virtual void onCameraChanged();
    virtual void onLightChanged();
    virtual void onEnvironmentChanged();
};

#include "shader.h"
#include "program.h"

#include "texture.h"
#include "material.h"

#include "object.h"
#include "model.h"
#include "simpleobjects.h"

#include "camera.h"

#include "light.h"

#include "scene.h"

#endif // __GRAPHENE_H__
