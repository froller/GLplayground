#include "graphene.h"
#include <math.h>

Graphene::Scene::Scene() : m_DefaultCamera(new Graphene::Camera::Targeted(fvec3(3, 3, 3), fvec3(0, 0, 0), 1.25f, M_PI_4))
{
    m_Camera = m_DefaultCamera;
    
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);
    
    glGenBuffers(2, m_Buffers);
    glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[BufferType::VertexBuffer]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Buffers[BufferType::ElementBuffer]);  
}

Graphene::Scene::~Scene()
{
    glDeleteBuffers(2, m_Buffers);
    glDeleteVertexArrays(1, &m_VAO);
    
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

unsigned int Graphene::Scene::VBO() const
{
    return m_Buffers[BufferType::VertexBuffer];
}

unsigned int Graphene::Scene::EBO() const
{
    return m_Buffers[BufferType::ElementBuffer];
}

const size_t Graphene::Scene::VBOsize() const
{
    size_t vboSize = 0;
    for (auto model = m_Models.begin(); model != m_Models.end(); ++model)
        vboSize += model->VBOsize();
    return vboSize;
}

const void *Graphene::Scene::fillVBO() const
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

const void *Graphene::Scene::fillEBO() const
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
