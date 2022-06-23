#include "graphene.h"

Graphene::OSD::OSD()
    :m_Width(1920)
    ,m_Height(1080)
    ,m_Started(false)
{
    m_Program = new Graphene::Program();  
    m_Surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, m_Width, m_Height);
    
    glGenBuffers(1, &m_UniformBuffer);
    
}

Graphene::OSD::~OSD()
{
    cairo_surface_destroy(m_Surface);
    glDeleteBuffers(1, &m_UniformBuffer);
    delete m_Program;
}

int Graphene::OSD::start()
{
    SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "Starting OSD");

    // Загрузка шейдеров
    addShader(Graphene::VertexShader,   std::filesystem::path("../osd-vert.glsl"));
    addShader(Graphene::GeometryShader, std::filesystem::path("../osd-geom.glsl"));
    addShader(Graphene::FragmentShader, std::filesystem::path("../osd-frag.glsl"));
    
    // Подключение шейдеров
    m_Program->use();    
       
    m_Started = true;
    return 0;
}

void Graphene::OSD::stop()
{
    SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "Stopping OSD");
    m_Started = false;
}


int Graphene::OSD::addShader(const ShaderType type, const std::string &source)
{
    Shader shader(type);
    shader.setSource(source);
    m_Program->addShader(shader);
    return 0;
}

int Graphene::OSD::addShader(const ShaderType type, const std::filesystem::path &path)
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

void Graphene::OSD::clear()
{
    cairo_t *cr = cairo_create(m_Surface);
    cairo_set_source_rgba (cr, 1.f, 1.f, 1.f, 0.f);
    cairo_set_operator (cr, CAIRO_OPERATOR_SOURCE);
    cairo_paint (cr);
    cairo_destroy(cr);
    cairo_surface_flush(m_Surface);
}

int Graphene::OSD::draw()
{
    if (!m_Started)
    {
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "OSD not started yet");
        return -1;
    }
    
    cairo_t *cr = cairo_create(m_Surface);
    
    // Тестовая рамка 1% от площади экрана
    cairo_rectangle(cr, 10.f, 10.f, m_Width / 10, m_Height / 10);
    cairo_set_line_width(cr, 2.f);
    cairo_set_line_join(cr, CAIRO_LINE_JOIN_MITER);
    cairo_set_line_cap(cr, CAIRO_LINE_CAP_SQUARE);
    cairo_set_source_rgba(cr, 0.5, 0.f, 1.f, 0.5);
    cairo_stroke(cr);
    
    cairo_destroy(cr);
    
    cairo_surface_flush(m_Surface);
    
    void * cairoFrameBuffer = cairo_image_surface_get_data(m_Surface);
    
    glBindBuffer(GL_UNIFORM_BUFFER, m_UniformBuffer);
    glBufferData(GL_UNIFORM_BUFFER, m_Width * m_Height * 4, cairoFrameBuffer, GL_STATIC_DRAW);   
    
    return 0;
}

void *Graphene::OSD::framebuffer()
{
     return cairo_image_surface_get_data(m_Surface);
     //glTexImage2D(GL_TEXTURE_2D, 0, 4, GLint(m_Width), GLint(m_Height), 0, GL_BGRA, GL_UNSIGNED_BYTE, data);
}
