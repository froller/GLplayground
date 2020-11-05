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
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
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

void Graphene::Scene::setAmbient(const Graphene::Color color)
{
    m_Ambient = color;
}


void Graphene::Scene::draw() const
{

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

unsigned int Graphene::Scene::VBO() const
{
    return m_Buffers[BufferType::VertexBuffer];
}

unsigned int Graphene::Scene::EBO() const
{
    return m_Buffers[BufferType::ElementBuffer];
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

size_t Graphene::Scene::VBOdata(void *vertexBuffer) const
{
    void *bufferTop = vertexBuffer;
    for (auto model = m_Models.begin(); model != m_Models.end(); ++model)
    {
        size_t modelBufferSize = model->VBOdata(bufferTop);
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

Graphene::Camera *Graphene::Scene::camera()
{
    return m_Camera;
}

fmat4 Graphene::Scene::model() const
{
    return fmat4(1);
}
