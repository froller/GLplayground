#include "graphene.h"

#define PIXEL_SIZE 4

Graphene::Texture::Texture()
{

}

Graphene::Texture::~Texture()
{
    if (m_Buffer)
        free(m_Buffer);
}

Graphene::Texture::Color::Color(Graphene::Color &color) : m_Color(color)
{
    m_Width = 1;
    m_Height = 1;
    m_Buffer = malloc(width() * height() * sizeof(RGB8));
    struct RGB8 *pixel = static_cast<struct RGB8 *>(m_Buffer);
    pixel[0].r = 0xFF * color.r;
    pixel[0].g = 0xFF * color.g;
    pixel[0].b = 0xFF * color.b;

    glGenTextures(1, &m_TextureID);
    glBindTexture(GL_TEXTURE_BUFFER, m_TextureID);
    glGenBuffers(1, &m_BufferID);
    glTexBuffer(GL_TEXTURE_BUFFER, GL_RGB8UI, m_BufferID);
}

void Graphene::Texture::Color::use()
{

}

Graphene::Texture::Checker::Checker(Graphene::Color &color1, Graphene::Color &color2) : m_Color1(color1), m_Color2(color2)
{
    m_Width = 2;
    m_Height = 2;
    m_Buffer = malloc(width() * height() * sizeof(RGB8));
    struct RGB8 *pixel = static_cast<struct RGB8 *>(m_Buffer);
    pixel[3].r = pixel[0].r = 0xFF * color1.r;
    pixel[3].g = pixel[0].g = 0xFF * color1.g;
    pixel[3].b = pixel[0].b = 0xFF * color1.b;
    pixel[2].r = pixel[1].r = 0xFF * color2.r;
    pixel[2].g = pixel[1].g = 0xFF * color2.g;
    pixel[2].b = pixel[1].b = 0xFF * color2.b;

};
