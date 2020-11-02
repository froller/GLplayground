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
    
//
// Это вообще тестовая заглушка. Еее не должно здесь быть. Вся эта хрень должна быть сделана в момент создания сцены.
//  
    fvec3 vertexBuffer[6] = {
        { 0.f,                1.f,  0.f },
        { sqrtf(3.f) / -2.f, -0.5,  0.f },
        { sqrtf(3.f) /  2.f, -0.5,  0.f },
        { 0.f,                1.f, -0.5 },
        { sqrtf(3.f) / -2.f, -0.5, -0.5 },
        { sqrtf(3.f) /  2.f, -0.5, -0.5 }
    };
    unsigned int elementBuffer[12] = { 0, 1, 2,  3, 4, 5,  2, 1, 4,  4, 5, 2 };
    
    m_Program->setUniform("MVP[0]", m_Scene->model());
    m_Program->setUniform("MVP[1]", m_Scene->camera()->view());
    m_Program->setUniform("MVP[2]", m_Scene->camera()->projection());

    m_Program->use();
    
    GLuint vertexBufferHandle;
    glGenBuffers(1, &vertexBufferHandle);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferHandle);   
    glBufferData(GL_ARRAY_BUFFER, sizeof(fvec3) * 6, vertexBuffer, GL_STATIC_DRAW);

    GLuint elementBufferHandle;
    glGenBuffers(1, &elementBufferHandle);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferHandle);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 3 * 4, elementBuffer, GL_STATIC_DRAW);

//
// Это должно выполняться на рендере каждого кадра
//
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferHandle);   
    glEnableVertexAttribArray(0); // 0 - просто потому что первый свободный индекс
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(fvec3), (void *)0);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferHandle);
    
    glDrawElements(GL_TRIANGLES, 3 * 4, GL_UNSIGNED_INT, (void *)0);

    glDisableVertexAttribArray(0);
    
//
// ...а это - уже нет. Это должно вызываться в перед разрушением сцены.
//
    glDeleteBuffers(1, &vertexBufferHandle);
    glDeleteBuffers(1, &elementBufferHandle);
    

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

void Graphene::setCamera(Graphene::Camera *camera) 
{
    m_Scene->setCamera(camera);
}

void Graphene::addModel(const Graphene::Model &model)
{
    m_Scene->addModel(model);
}

#ifdef GRAPHENE_EXPOSE_INTERNALS
Graphene::Scene * Graphene::scene() const
{
    return m_Scene;
}

Graphene::Program * Graphene::program() const
{
    return m_Program;
}
#endif

void Graphene::clear() const
{
    glClearColor(0.0, 0.5, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
