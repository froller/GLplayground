#include "graphene.h"

#define PIXEL_SIZE 4

Graphene::Texture::~Texture()
{
    if (m_Buffer)
        free(m_Buffer);
}

Graphene::Texture::Color::Color(Graphene::Color &color) : m_Color(color)
{
    m_Width = 1;
    m_Height = 1;
    m_Buffer = malloc(width() * height() * PIXEL_SIZE); // FIXME magic number
}

Graphene::Texture::Checker::Checker(Graphene::Color &color1, Graphene::Color &color2) : m_Color1(color1), m_Color2(color2)
{
    m_Width = 2;
    m_Height = 2;
    m_Buffer = malloc(width() * height() * PIXEL_SIZE); // FIXME magic number
};
