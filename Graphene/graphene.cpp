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
    
    // Создание VBO и SSBO
    glGenBuffers(BufferType::BufferTypeMax, m_Buffers);

    // Использование буфера глубины
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    
    // Настройки фрембуфера
    glEnable(GL_FRAMEBUFFER_SRGB);
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

    // Удаление VBO и SSBO
    glDeleteBuffers(BufferType::BufferTypeMax, m_Buffers);
    
    // Удаление VAO
    glDeleteVertexArrays(1, &m_VAO);

    // Удаление сцены
    delete m_Scene;
    
    // Удаление шейдеров
    delete m_Program;
}

int Graphene::draw()
{
    clear();

    m_Program->use();

    // Заполнение буферов
    fillVertexBuffer();
    fillElementBuffer();
    fillLightBuffer();

    // Заполнение юниформов
    m_Program->setUniform("MVP[0]", m_Scene->model());
    m_Program->setUniform("MVP[1]", m_Scene->camera()->view());
    m_Program->setUniform("MVP[2]", m_Scene->camera()->projection());
    m_Program->setUniform("cameraPos", m_Scene->camera()->m_Position);
    m_Program->setUniform("ambientColor", m_Scene->m_Ambient);

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
    // Примитивы
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Buffers[BufferType::ElementBuffer]);
    // Источники света
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_Buffers[BufferType::LightBuffer]);
    glBindBufferRange(GL_SHADER_STORAGE_BUFFER, 0, m_Buffers[BufferType::LightBuffer], 0, m_LightBufferSize);

    
#ifdef WIREFRAME
    for (size_t i = 0; i < ElementSize * m_Scene->elementCount(); i += ElementSize)
        glDrawElements(GL_LINE_LOOP, ElementSize, GL_UNSIGNED_INT, (void *)(i * sizeof(Index)));
#else
    glDrawElements(GL_TRIANGLES, ElementSize * m_Scene->elementCount(), GL_UNSIGNED_INT, (void *)0);
#endif // WIREFRAME
 
    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);
    
    return 0;
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

void Graphene::setCamera(Graphene::Camera *camera) 
{
    m_Scene->setCamera(camera);
}

void Graphene::addModel(const Graphene::Model &model)
{
    m_Scene->addModel(model);
}

void Graphene::addLight(const Graphene::Light &light)
{
    m_Scene->addLight(light);
    m_Program->setUniform("lightsCount", static_cast<unsigned int>(m_Scene->lightCount()));
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

/*****************************************************************************/

size_t Graphene::reAllocateVertexBuffer()
{
    size_t newSize = m_Scene->VBOsize();
    if (newSize > m_VertexBufferSize)
    {
        m_VertexBuffer = realloc(m_VertexBuffer, newSize);
        m_VertexBufferSize = newSize;
    }
    return m_ElementBufferSize;
}

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

void Graphene::fillVertexBuffer()
{
    reAllocateVertexBuffer();
    m_Scene->VBOdata(m_VertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_Scene->vertexCount(), m_VertexBuffer, GL_STATIC_DRAW);
}

void Graphene::fillElementBuffer()
{
    reAllocateElementBuffer();
    m_Scene->EBOdata(m_ElementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Element) * m_Scene->elementCount(), m_ElementBuffer, GL_STATIC_DRAW);
}

void Graphene::fillLightBuffer()
{
    reAllocateLightBuffer();
    size_t lightsBufferSize = m_Scene->lightCount() * sizeof(LightSource);
    m_Scene->lightsData(m_LightBuffer);
    glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(LightSource) * m_Scene->lightCount(), m_LightBuffer, GL_STATIC_DRAW);
}
