#include "graphene.h"

#include <string.h>
#include <stdlib.h>

/*******************************************************************************
 * 
 * Graphene
 * 
 ******************************************************************************/

Graphene::Graphene()
{
    m_Scene = std::make_shared<Scene>();
    m_ClearColor = { 0, 0, 0 };
    
    // Создание VAO
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);
    
    // Создание буферов
    glGenBuffers(BufferType::BufferTypeMax, m_Buffers);

    // Использование буфера глубины
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    
    // Настройки фреймбуфера
    glEnable(GL_FRAMEBUFFER_SRGB);
    
    // Куллинг
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

Graphene::~Graphene()
{
    // Освобождение памяти
    if (m_VertexBuffer)
        free(m_VertexBuffer);
    if (m_ElementBuffer)
        free(m_ElementBuffer);
    if (m_StorageBuffer)
        free(m_StorageBuffer);
    if (m_UniformBuffer)
        free(m_UniformBuffer);

    // Удаление буферов
    glDeleteBuffers(BufferType::BufferTypeMax, m_Buffers);
    
    // Удаление VAO
    glDeleteVertexArrays(1, &m_VAO);
}

int Graphene::draw()
{
    if (m_Scene->modified() & Scene::Aspect::Geometry)
        onGeometryChanged();
    if (m_Scene->modified() & Scene::Aspect::Light)
        onLightChanged();
    if (m_Scene->modified() & Scene::Aspect::Camera)
        onCameraChanged();
    if (m_Scene->modified() & Scene::Aspect::Environment)
        onEnvironmentChanged();
    if (m_Scene->modified() & Scene::Aspect::Shaders)
        onShaderChanged();

    clear();
    
//
// Это должно выполняться на рендере каждого кадра
//
    // Координаты
    glEnableVertexAttribArray(0); // 0 - просто потому что первый свободный индекс
    glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[BufferType::VertexBuffer]);   
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, position));
    // Нормали
    glEnableVertexAttribArray(1); // 1 - просто потому что следующий свободный
    glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[BufferType::VertexBuffer]);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, sizeof(Vertex), (void *)offsetof(Vertex, normal));
    // Текстурные координаты
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[BufferType::VertexBuffer]);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, UV));
    // ID сетки
    glEnableVertexAttribArray(3);
    glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[BufferType::VertexBuffer]);
    glVertexAttribIPointer(3, 1, GL_UNSIGNED_INT, sizeof(Vertex), (void *)offsetof(Vertex, meshId));
    // Примитивы
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Buffers[BufferType::ElementBuffer]);
    // Источники света
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_Buffers[BufferType::StorageBuffer]);
    glBindBufferRange(GL_SHADER_STORAGE_BUFFER, 0, m_Buffers[BufferType::StorageBuffer], 0, m_Scene->lightRangeSize());
    glBindBufferRange(GL_SHADER_STORAGE_BUFFER, 1, m_Buffers[BufferType::StorageBuffer], m_Scene->lightRangeSize(), m_Scene->modelRangeSize());
    // Матрицы кмеры
    glBindBuffer(GL_UNIFORM_BUFFER, m_Buffers[BufferType::UniformBuffer]);
    glBindBufferRange(GL_UNIFORM_BUFFER, 0, m_Buffers[BufferType::UniformBuffer], 0, sizeof(CameraMatrices));
    
    if (m_Wireframe)
        for (size_t i = 0; i < ElementSize * m_Scene->elementCount(); i += ElementSize)
            glDrawElements(GL_LINE_LOOP, ElementSize, GL_UNSIGNED_INT, (void *)(i * sizeof(Index)));
    else
        glDrawElements(GL_TRIANGLES, ElementSize * m_Scene->elementCount(), GL_UNSIGNED_INT, (void *)0);
 
    glDisableVertexAttribArray(3);
    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);
    
    return 0;
}

std::shared_ptr<Graphene::Scene> Graphene::scene() const
{
    return m_Scene;   
}

void Graphene::camera(std::shared_ptr<Graphene::Camera> camera) 
{
    m_Scene->camera(camera);
}

void Graphene::addModel(const Graphene::Model &model)
{
    m_Scene->addModel(model);
}

void Graphene::addLight(const Graphene::Light &light)
{
    m_Scene->addLight(light);
}

void Graphene::setClearColor(const Color &color)
{
    m_ClearColor = color;
}

void Graphene::clear() const
{
    glClearColor(m_ClearColor.r, m_ClearColor.g, m_ClearColor.b, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool Graphene::cull() const
{
    return glIsEnabled(GL_CULL_FACE);
}

void Graphene::cull(const bool enable)
{
    if (enable)
        glEnable(GL_CULL_FACE);
    else
        glDisable(GL_CULL_FACE);
}

bool Graphene::gammaCorrection() const
{
    return glIsEnabled(GL_FRAMEBUFFER_SRGB);
}

void Graphene::gammaCorrection(const bool enable)
{
    if (enable)
        glEnable(GL_FRAMEBUFFER_SRGB);
    else
        glDisable(GL_FRAMEBUFFER_SRGB);
}

bool Graphene::wireframe() const
{
    return m_Wireframe;
}

void Graphene::wireframe(const bool enable)
{
    m_Wireframe = enable;
}

/*****************************************************************************/

size_t Graphene::reAllocateElementBuffer()
{
    size_t newSize = m_Scene->EBOsize();
    if (newSize > m_ElementBufferSize)
    {
        void *ptr = realloc(m_ElementBuffer, newSize);
        m_ElementBuffer = ptr;
        m_ElementBufferSize = newSize;
    }
    return m_ElementBufferSize;
}

size_t Graphene::reAllocateVertexBuffer()
{
    size_t newSize = m_Scene->VBOsize();
    if (newSize > m_VertexBufferSize)
    {
        void *ptr = realloc(m_VertexBuffer, newSize);
        m_VertexBuffer = ptr;
        m_VertexBufferSize = newSize;
    }
    return m_VertexBufferSize;
}

size_t Graphene::reAllocateStorageBuffer()
{
    size_t newSize = m_Scene->SSBOsize();
    if (newSize > m_StorageBufferSize)
    {
        void *ptr = realloc(m_StorageBuffer, newSize);
        m_StorageBuffer = ptr;
        m_StorageBufferSize = newSize;
    }
    return m_StorageBufferSize;
}

size_t Graphene::reAllocateUniformBuffer()
{
    size_t newSize = m_Scene->UBOsize();
    if (newSize > m_UniformBufferSize)
    {
        void *ptr = realloc(m_UniformBuffer, newSize);
        m_UniformBuffer = ptr;
        m_UniformBufferSize = newSize;
    }
    return m_UniformBufferSize;
}

void Graphene::fillVertexBuffer()
{
    reAllocateVertexBuffer();
    m_Scene->VBOdata(m_VertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[BufferType::VertexBuffer]);   
    glBufferData(GL_ARRAY_BUFFER, m_Scene->VBOsize(), m_VertexBuffer, GL_STATIC_DRAW);
}

void Graphene::fillElementBuffer()
{
    reAllocateElementBuffer();
    m_Scene->EBOdata(m_ElementBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Buffers[BufferType::ElementBuffer]);   
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Scene->EBOsize(), m_ElementBuffer, GL_STATIC_DRAW);
}

void Graphene::fillStorageBuffer()
{
    reAllocateStorageBuffer();
    m_Scene->SSBOdata(m_StorageBuffer);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_Buffers[BufferType::StorageBuffer]);   
    glBufferData(GL_SHADER_STORAGE_BUFFER, m_Scene->SSBOsize(), m_StorageBuffer, GL_STATIC_DRAW);
}

void Graphene::fillUniformBuffer()
{
    reAllocateUniformBuffer();
    m_Scene->UBOdata(m_UniformBuffer);
    glBindBuffer(GL_UNIFORM_BUFFER, m_Buffers[BufferType::UniformBuffer]);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(CameraMatrices), m_UniformBuffer, GL_STATIC_DRAW);
}

void Graphene::useMaterials()
{
    for (auto m = m_Scene->materials().begin(); m != m_Scene->materials().end(); ++m)
        (*m)->m_Program.use();
}

void Graphene::onGeometryChanged()
{
    // Заполнение буферов
    fillVertexBuffer();
    fillElementBuffer();
//    fillUniformBuffer();
    m_Scene->depict(Scene::Aspect::Geometry);
}

void Graphene::onCameraChanged()
{
    fillUniformBuffer();
    m_Scene->depict(Scene::Aspect::Camera);
}

void Graphene::onLightChanged()
{
    fillStorageBuffer();   
    m_Scene->depict(Scene::Aspect::Light);
}

void Graphene::onEnvironmentChanged()
{
    fillStorageBuffer();   
    m_Scene->depict(Scene::Aspect::Environment);
}

void Graphene::onShaderChanged()
{
    useMaterials();
    m_Scene->depict(Scene::Aspect::Shaders);
}
