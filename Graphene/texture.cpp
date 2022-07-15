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

Graphene::Texture::Color::Color(const Graphene::Color &color) : m_Color(color)
{
    m_Width = 1;
    m_Height = 1;
    size_t bufferSize = width() * height() * sizeof(RGB8);
    m_Buffer = malloc(bufferSize);
    struct RGB8 *pixel = static_cast<struct RGB8 *>(m_Buffer);
    pixel[0].r = 0xFF * color.r;
    pixel[0].g = 0xFF * color.g;
    pixel[0].b = 0xFF * color.b;

    glGenTextures(1, &m_TextureID);
    glBindTexture(GL_TEXTURE_2D, m_TextureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width(), height(), 0, GL_BGR, GL_UNSIGNED_BYTE, m_Buffer);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

/*
void Graphene::Texture::Color::use()
{

}
*/

Graphene::Texture::Checker::Checker(const Graphene::Color &color1, const Graphene::Color &color2) : m_Color1(color1), m_Color2(color2)
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

    glGenTextures(1, &m_TextureID);
    glBindTexture(GL_TEXTURE_2D, m_TextureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

/*
    glGenBuffers(1, &m_BufferID);
    glTexBuffer(, GL_RGB8UI, m_BufferID);
    glBufferData(, bufferSize, m_Buffer, GL_STATIC_DRAW);
*/
};
