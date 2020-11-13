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
}

Graphene::~Graphene()
{
    delete m_Program;
}

int Graphene::run()
{
    clear();

    m_Program->use();

    // Аллокация буферов
    void *vertexBuffer = malloc(m_Scene->VBOsize());
    void *elementBuffer = malloc(m_Scene->EBOsize());
    
    // Заполнение буферов
    m_Scene->VBOdata(vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_Scene->vertexCount(), vertexBuffer, GL_STATIC_DRAW);

    m_Scene->EBOdata(elementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Element) * m_Scene->elementCount(), elementBuffer, GL_STATIC_DRAW);
    
// Это меняется только при изменении камеры
    m_Program->setUniform("MVP[0]", m_Scene->model());
    m_Program->setUniform("MVP[1]", m_Scene->camera()->view());
    m_Program->setUniform("MVP[2]", m_Scene->camera()->projection());

// Это должно быть перенесено в сцену
    m_Program->setUniform("ambientColor", m_Scene->m_Ambient);

    size_t lightsBufferSize = m_Scene->lightsCount() * sizeof(LightSource);
    void *lightsBuffer = malloc(lightsBufferSize);
    m_Scene->lightsData(lightsBuffer);
    glBindBufferRange(GL_SHADER_STORAGE_BUFFER, 0, m_Scene->m_Buffers[Graphene::Scene::BufferType::LightsBuffer], 0, lightsBufferSize);
    glBufferData(GL_SHADER_STORAGE_BUFFER, lightsBufferSize, lightsBuffer, GL_STATIC_DRAW);
    m_Program->setUniform("lightsCount", static_cast<unsigned int>(m_Scene->lightsCount()));

//
// Это должно выполняться на рендере каждого кадра
//
    // Координаты
    glEnableVertexAttribArray(0); // 0 - просто потому что первый свободный индекс
    glBindBuffer(GL_ARRAY_BUFFER, m_Scene->VBO());   
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, position));
    // Нормали
    glEnableVertexAttribArray(1); // 1 - просто потому что следующий свободный
    glBindBuffer(GL_ARRAY_BUFFER, m_Scene->VBO());
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, normal));
    // Цвета
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, m_Scene->VBO());
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, color));
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Scene->EBO());
    
#ifdef WIREFRAME
    for (size_t i = 0; i < ElementSize * m_Scene->elementCount(); i += ElementSize)
        glDrawElements(GL_LINE_LOOP, ElementSize, GL_UNSIGNED_INT, (void *)(i * sizeof(Index)));
#else
    glDrawElements(GL_TRIANGLES, ElementSize * m_Scene->elementCount(), GL_UNSIGNED_INT, (void *)0);
#endif // WIREFRAME

    free(lightsBuffer);
    
    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);
    
    free(vertexBuffer);
    free(elementBuffer);

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

void Graphene::setClearColor(const Color color)
{
    m_ClearColor = color;
}

void Graphene::clear() const
{
    glClearColor(m_ClearColor.r, m_ClearColor.g, m_ClearColor.b, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}