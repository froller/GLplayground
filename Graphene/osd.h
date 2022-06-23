#ifndef __OSD_H__
#define __OSD_H__

#include <cairo.h>
#include "program.h"

/*******************************************************************************
 * 
 * Graphene::OSD
 * 
 ******************************************************************************/

class Graphene::OSD
{
public:
    OSD();
    virtual ~OSD();
    
protected:
    Graphene::Program *m_Program;
    float m_Width;
    float m_Height;
    cairo_device_t *m_Device;
    cairo_surface_t *m_Surface;
    cairo_t *m_Context;
    bool m_Started;
    GLuint m_UniformBuffer;
    
public:
    virtual int start();
    virtual void stop();
    virtual int addShader(const ShaderType type, const std::string &source);
    virtual int addShader(const ShaderType type, const std::filesystem::path &path);
    virtual void clear();
    virtual int draw();
    virtual void *framebuffer();
};

#endif // __OSD_H__
