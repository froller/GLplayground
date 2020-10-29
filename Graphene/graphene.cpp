#include "graphene.h"

#include <string.h>

/*******************************************************************************
 * 
 * Graphene
 * 
 ******************************************************************************/

Graphene::Graphene()
{
    m_Program = new Program();
    m_Scene = new Scene();
}

Graphene::~Graphene()
{
    delete m_Program;
}

int Graphene::run()
{
    clear();

//     const void *sceneVBO = m_Scene->VBO();
//     const void *sceneEBO = m_Scene->EBO();
    
    GLuint bufferHandles[1];
    glCreateBuffers(1, bufferHandles);
    
    fvec3 vertexBuffer[6] = {
        { 0.f,                1.f,  0.f },
        { sqrtf(3.f) / -2.f, -0.5,  0.f },
        { sqrtf(3.f) /  2.f, -0.5,  0.f },
        { 0.f,                1.f, -0.1 },
        { sqrtf(3.f) / -2.f, -0.5, -0.1 },
        { sqrtf(3.f) /  2.f, -0.5, -0.1 }
    };
    GLuint elementBuffer[6] = { 0, 1, 2, 3, 4, 5};

    m_Program->use();
    
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, bufferHandles[0]);
    glVertexAttribPointer(
        0,                  // Атрибут 0. Подробнее об этом будет рассказано в части, посвященной шейдерам.
        3,                  // Размер
        GL_FLOAT,           // Тип
        GL_FALSE,           // Указывает, что значения не нормализованы
        0,                  // Шаг
        (void*)0            // Смещение массива в буфере
    );
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBuffer), vertexBuffer, GL_STATIC_DRAW);
    
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glDisableVertexAttribArray(0);
    
    glDeleteBuffers(1, bufferHandles);

//     free((void *)sceneVBO);
//     free((void *)sceneEBO);

    return 0;
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

Graphene::Scene * Graphene::scene() const
{
    return m_Scene;
}


void Graphene::clear() const
{
    glClearColor(0.0, 0.5, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
