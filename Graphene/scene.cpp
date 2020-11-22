#include "graphene.h"

Graphene::Scene::Scene() : m_DefaultCamera(new Graphene::Camera::Targeted(fvec3(3, 3, 3), fvec3(0, 0, 0), 1.25f, M_PI_4))
{
    m_Camera = m_DefaultCamera;
    m_Ambient = Color(0.f, 0.f, 0.f);
    m_Modified = Aspect::All;
}

Graphene::Scene::~Scene()
{
    delete m_DefaultCamera;   
}

uint16_t Graphene::Scene::modified() const
{
    return m_Modified;
}

void Graphene::Scene::touch(Graphene::Scene::Aspect aspect)
{
    m_Modified |= aspect;
}

void Graphene::Scene::depict(Graphene::Scene::Aspect aspect)
{
    m_Modified &= ~aspect;
}

void Graphene::Scene::resetCamera()
{
    m_Camera = m_DefaultCamera;
    m_Modified |= Aspect::Camera;
}

Graphene::Camera *Graphene::Scene::camera() const
{
    return m_Camera;
}

void Graphene::Scene::camera(Graphene::Camera *camera)
{
    m_Camera = camera;
    m_Modified |=  Aspect::Camera;
}

void Graphene::Scene::addModel(const Graphene::Model &model)
{
    m_Models.push_back(model);
    m_Modified |=  Aspect::Geometry;
}

void Graphene::Scene::addLight(const Graphene::Light &light)
{
    m_Lights.push_back(light);
    m_Modified |=  Aspect::Light;
}

Graphene::Color Graphene::Scene::ambient() const
{
    return m_Ambient;
}

void Graphene::Scene::ambient(const Graphene::Color color)
{
    m_Ambient = color;
    m_Modified |= Aspect::Environment;
}

size_t Graphene::Scene::vertexCount() const
{
    size_t count = 0;
    for (auto &model : m_Models)
        count += model.vertexCount();
    return count;
}

size_t Graphene::Scene::elementCount() const
{
    size_t count = 0;
    for (auto &model : m_Models)
        count += model.elementCount();
    return count;
}

size_t Graphene::Scene::lightCount() const
{
    return m_Lights.size();
}

size_t Graphene::Scene::modelCount() const
{
    return m_Models.size();
}

size_t Graphene::Scene::VBOsize() const
{
    size_t vboSize = 0;
    for (auto model = m_Models.begin(); model != m_Models.end(); ++model)
        vboSize += model->VBOsize();
    return vboSize;
}

size_t Graphene::Scene::EBOsize() const
{
    size_t eboSize = 0;
    for (auto model = m_Models.begin(); model != m_Models.end(); ++model)
        eboSize += model->EBOsize();
    return eboSize;
}

size_t Graphene::Scene::UBOsize() const
{
    return sizeof(CameraMatrices);
}

size_t Graphene::Scene::SSBOsize() const
{
    return sizeof(unsigned int)
        + lightCount() * sizeof(LightSource)
        + sizeof(unsigned int)
        + modelCount() * sizeof(ModelMatrices);
}

size_t Graphene::Scene::VBOdata(void *vertexBuffer) const
{
    void *bufferTop = vertexBuffer;
    for (auto model = m_Models.begin(); model != m_Models.end(); ++model)
    {
        size_t modelBufferSize = model->VBOdata(bufferTop);
        // FIXME заполнять meshId
        bufferTop = (char *)bufferTop + modelBufferSize;
    }
    return (char *)bufferTop - (char *)vertexBuffer;
}

size_t Graphene::Scene::EBOdata(void *elementBuffer) const
{
    void *bufferTop = elementBuffer;
    Index indexOffset = 0;
    for (auto model = m_Models.begin(); model != m_Models.end(); ++model)
    {
        size_t modelBufferSize = model->EBOdata(bufferTop, indexOffset);
        bufferTop = (char *)bufferTop + modelBufferSize;
        indexOffset += model->vertexCount();
    }
    return (char *)bufferTop - (char *)elementBuffer;
}

size_t Graphene::Scene::SSBOdata(void* storageBuffer) const
{
    void *bufferTop = storageBuffer;
    for (auto light = m_Lights.begin(); light != m_Lights.end(); ++light)
    {
        light->lightData(bufferTop);
        bufferTop = (char *)bufferTop + sizeof(LightSource);
    }
    for (auto model = m_Models.begin(); model != m_Models.end(); ++model)
    {
        model->SSBOdata(bufferTop);
        bufferTop = (char *)bufferTop + sizeof(ModelMatrices);
    }
    return (char *)bufferTop - (char *)storageBuffer;
}

size_t Graphene::Scene::UBOdata(void *uniformBuffer) const
{
    void *bufferTop = uniformBuffer;
    CameraMatrices *cameraMatrices = (CameraMatrices *)bufferTop;
    cameraMatrices->world = fmat4({1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, -1, 0}, {0, 0, 0, 1});
    cameraMatrices->view = m_Camera->view();
    cameraMatrices->projection = m_Camera->projection();
    cameraMatrices->position = m_Camera->position();
    bufferTop = (char *)bufferTop + sizeof(CameraMatrices);
    // ...
    return (char *)bufferTop - (char *)uniformBuffer;
}

fmat4 Graphene::Scene::model() const
{
    return fmat4(1);
}
