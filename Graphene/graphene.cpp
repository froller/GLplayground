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
    m_Program = new Program();
    m_Scene = new Scene();
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
    if (m_LightBuffer)
        free(m_LightBuffer);

    // Удаление буферов
    glDeleteBuffers(BufferType::BufferTypeMax, m_Buffers);
    
    // Удаление VAO
    glDeleteVertexArrays(1, &m_VAO);

    // Удаление сцены
    delete m_Scene;
    
    // Удаление шейдеров
    delete m_Program;
}

int Graphene::start()
{
    SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "Starting Graphene");

    // Подключение шейдера
    m_Program->use();    
       
    m_Started = true;
    return 0;
}

int Graphene::draw()
{
    if (!m_Started)
    {
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Graphene not started yet");
        return -1;
    }
    
    if (m_Scene->modified() & Scene::Aspect::Geometry)
        onGeometryChanged();
    if (m_Scene->modified() & Scene::Aspect::Light)
        onLightChanged();
    if (m_Scene->modified() & Scene::Aspect::Camera)
        onCameraChanged();
    if (m_Scene->modified() & Scene::Aspect::Environment)
        onEnvironmentChanged();

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
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, normal));
    // Цвета
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[BufferType::VertexBuffer]);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, color));
    // Текстурные координаты
    glEnableVertexAttribArray(3);
    glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[BufferType::VertexBuffer]);
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, UV));
    // ID сетки
    glEnableVertexAttribArray(4);
    glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[BufferType::VertexBuffer]);
    glVertexAttribPointer(4, 1, GL_UNSIGNED_INT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, meshId));
    // Примитивы
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Buffers[BufferType::ElementBuffer]);
    // Источники света
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_Buffers[BufferType::LightBuffer]);
    glBindBufferRange(GL_SHADER_STORAGE_BUFFER, 0, m_Buffers[BufferType::LightBuffer], 0, m_LightBufferSize);

    if (m_Wireframe)
        for (size_t i = 0; i < ElementSize * m_Scene->elementCount(); i += ElementSize)
            glDrawElements(GL_LINE_LOOP, ElementSize, GL_UNSIGNED_INT, (void *)(i * sizeof(Index)));
    else
        glDrawElements(GL_TRIANGLES, ElementSize * m_Scene->elementCount(), GL_UNSIGNED_INT, (void *)0);
 
    glDisableVertexAttribArray(4);
    glDisableVertexAttribArray(3);
    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);
    
    return 0;
}

void Graphene::stop()
{
    SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "Stopping Graphene");
    m_Started = false;
}

Graphene::Scene *Graphene::scene() const
{
    return m_Scene;   
}

int Graphene::addShader(const ShaderType type, const std::string &source)
{
    Shader shader(type);
    shader.setSource(source);
    m_Program->addShader(shader);
    return 0;
}

int Graphene::addShader(const ShaderType type, const std::filesystem::path &path)
{
    Shader shader(type);
    if (shader.loadSource(path))
    {
        SDL_LogCritical(SDL_LOG_CATEGORY_VIDEO, "Error loading shader source: %s\n", shader.log());
        return -1;
    }
    m_Program->addShader(shader);
    return 0;
}

void Graphene::camera(Graphene::Camera *camera) 
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

void Graphene::setClearColor(const Color color)
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
        m_ElementBuffer = realloc(m_ElementBuffer, newSize);
        m_ElementBufferSize = newSize;
    }
    return m_ElementBufferSize;
}

size_t Graphene::reAllocateVertexBuffer()
{
    size_t newSize = m_Scene->VBOsize();
    if (newSize > m_VertexBufferSize)
    {
        m_VertexBuffer = realloc(m_VertexBuffer, newSize);
        m_VertexBufferSize = newSize;
    }
    return m_VertexBufferSize;
}

size_t Graphene::reAllocateLightBuffer()
{
    size_t newSize = m_Scene->lightCount() * sizeof(LightSource);
    if (newSize > m_LightBufferSize)
    {
        m_LightBuffer = realloc(m_LightBuffer, newSize);
        m_LightBufferSize = newSize;
    }
    return m_LightBufferSize;
}

size_t Graphene::reAllocateUniformBuffer()
{
    size_t newSize = m_Scene->UBOsize();
    if (newSize > m_UniformBufferSize)
    {
        m_UniformBuffer = realloc(m_UniformBuffer, newSize);
        m_UniformBufferSize = newSize;
    }
    return m_UniformBufferSize;
}

void Graphene::fillVertexBuffer()
{
    reAllocateVertexBuffer();
    m_Scene->VBOdata(m_VertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[BufferType::VertexBuffer]);   
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_Scene->vertexCount(), m_VertexBuffer, GL_STATIC_DRAW);
}

void Graphene::fillElementBuffer()
{
    reAllocateElementBuffer();
    m_Scene->EBOdata(m_ElementBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Buffers[BufferType::ElementBuffer]);   
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Element) * m_Scene->elementCount(), m_ElementBuffer, GL_STATIC_DRAW);
}

void Graphene::fillLightBuffer()
{
    reAllocateLightBuffer();
    m_Scene->SSBOdata(m_LightBuffer);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_Buffers[BufferType::LightBuffer]);   
    glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(LightSource) * m_Scene->lightCount(), m_LightBuffer, GL_STATIC_DRAW);
}

void Graphene::fillUniformBuffer()
{
    reAllocateUniformBuffer();
    m_Scene->UBOdata(m_UniformBuffer);
    glBindBuffer(GL_UNIFORM_BUFFER, m_Buffers[BufferType::UniformBuffer]);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(CameraMatrices), m_UniformBuffer, GL_STATIC_DRAW);
    glBindBufferRange(GL_UNIFORM_BUFFER, 0, m_Buffers[BufferType::UniformBuffer], 0, sizeof(CameraMatrices));
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
//    m_Program->setUniform("MVP[0]", m_Scene->model());
//    m_Program->setUniform("MVP[1]", m_Scene->camera()->view());
//    m_Program->setUniform("MVP[2]", m_Scene->camera()->projection());
//    m_Program->setUniform("cameraPosition", m_Scene->camera()->m_Position);
    fillUniformBuffer();
    m_Scene->depict(Scene::Aspect::Camera);
}

void Graphene::onLightChanged()
{
    fillLightBuffer();   
    m_Program->setUniform("lightsCount", static_cast<unsigned int>(m_Scene->lightCount()));
    m_Scene->depict(Scene::Aspect::Light);
}

void Graphene::onEnvironmentChanged()
{
    m_Program->setUniform("ambientColor", m_Scene->ambient());
    m_Scene->depict(Scene::Aspect::Environment);
}
