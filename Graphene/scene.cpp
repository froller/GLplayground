#include "graphene.h"
#include <math.h>

Graphene::Scene::Scene() : m_DefaultCamera(new Graphene::Camera::Targeted(fvec3(0, 0, 2), fvec3(0, 0, 0), 1.25f, M_PI_4))
{
    m_Camera = m_DefaultCamera;
}

Graphene::Scene::~Scene()
{
    delete m_DefaultCamera;   
}

void Graphene::Scene::resetCamera()
{
    m_Camera = m_DefaultCamera;
}

void Graphene::Scene::setCamera(Graphene::Camera *camera)
{
    m_Camera = camera;
}

void Graphene::Scene::addModel(const Graphene::Model &model)
{
    m_Models.push_back(model);
}

const unsigned int Graphene::Scene::vertexCount() const
{
    size_t count = 0;
    for (auto model = m_Models.begin(); model != m_Models.end(); ++model)
        count += model->vertexCount();
    return count;
}

const size_t Graphene::Scene::VBOsize() const
{
    size_t vboSize = 0;
    for (auto model = m_Models.begin(); model != m_Models.end(); ++model)
        vboSize += model->VBOsize();
    return vboSize;
}

const void *Graphene::Scene::VBO() const
{
    void *vbo = malloc(VBOsize());
    void *vboTop = vbo;
    for (auto model = m_Models.begin(); model != m_Models.end(); ++model)
    {
        memcpy(vboTop, model->VBO(), model->VBOsize());
        vboTop = (char *)vboTop + model->VBOsize();
    }
    return vbo;
}

const size_t Graphene::Scene::EBOsize() const
{
    size_t eboSize = 0;
    for (auto model = m_Models.begin(); model != m_Models.end(); ++model)
        eboSize += model->EBOsize();
    return eboSize;
}

const void *Graphene::Scene::EBO() const
{
    void *ebo = malloc(EBOsize());
    void *eboTop = ebo;
    for (auto model = m_Models.begin(); model != m_Models.end(); ++model)
    {
        memcpy(eboTop, model->EBO(), model->EBOsize());
        eboTop = (char *)eboTop + model->EBOsize();
    }
    return ebo;
}

Graphene::Camera *Graphene::Scene::camera()
{
    return m_Camera;
}

fmat4 Graphene::Scene::model() const
{
    return fmat4(1);
}
