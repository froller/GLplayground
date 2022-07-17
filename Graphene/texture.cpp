#include "graphene.h"

#define PIXEL_SIZE 4

Graphene::Texture::Texture()
{
    glGenBuffers(1, &m_BufferID);
}

Graphene::Texture::~Texture()
{
    glDeleteBuffers(1, &m_BufferID);
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
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width(), height(), 0, GL_RGB, GL_UNSIGNED_BYTE, m_Buffer);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    //glGenerateMipmap(GL_TEXTURE_2D);   // пока подождет
    
    glBindBuffer(GL_TEXTURE_BUFFER, m_BufferID);
    glBufferData(GL_TEXTURE_BUFFER, bufferSize, m_Buffer, GL_STATIC_DRAW);
}

Graphene::Texture::Checker::Checker(const Graphene::Color &color1, const Graphene::Color &color2) : m_Color1(color1), m_Color2(color2)
{
    m_Width = 2;
    m_Height = 2;
    size_t bufferSize = width() * height() * sizeof(RGB8);
    m_Buffer = malloc(16);
    uint8_t *foo = static_cast<uint8_t *>(m_Buffer);
    foo[0] = foo[11] = 0xFF * color1.r;
    foo[1] = foo[12] = 0xFF * color1.g;
    foo[2] = foo[13] = 0xFF * color1.b;
    foo[3] = foo[8]  = 0xFF * color2.r;
    foo[4] = foo[9]  = 0xFF * color2.g;
    foo[5] = foo[10] = 0xFF * color2.b;

    glGenTextures(1, &m_TextureID);
    glBindTexture(GL_TEXTURE_2D, m_TextureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width(), height(), 0, GL_RGB, GL_UNSIGNED_BYTE, m_Buffer);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    //glGenerateMipmap(GL_TEXTURE_2D);   // пока подождет

    glBindBuffer(GL_TEXTURE_BUFFER, m_BufferID);
    glBufferData(GL_TEXTURE_BUFFER, bufferSize, m_Buffer, GL_STATIC_DRAW);
};
