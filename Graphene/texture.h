#ifndef __TEXTURE_H__
#define __TEXTURE_H__

class Graphene::Texture
{
public:
    class Color;
    class Checker;
    enum class Type {
        None = 0,
        Color,
        Checker
    };
    
    constexpr static const Type s_Type = Type::None;
    constexpr static const Type type() { return s_Type; };

public:
    Texture() = default;
    virtual ~Texture();
    constexpr size_t width() const { return m_Width; }
    constexpr size_t height() const { return m_Height; }
    constexpr void *buffer() const { return m_Buffer; }

protected:
    size_t m_Width = 0;
    size_t m_Height = 0;
    void *m_Buffer = nullptr;
};

class Graphene::Texture::Color : public Graphene::Texture
{
public:
    constexpr static const Type s_Type = Type::Color;
    constexpr static const Type type() { return s_Type; };
    
public:
    Color(Graphene::Color &color);
    virtual ~Color() = default;

protected:
    Graphene::Color m_Color;
};

class Graphene::Texture::Checker : public Graphene::Texture
{
public:
    constexpr static const Type s_Type = Type::Checker;
    constexpr static const Type type() { return s_Type; };

public:
    Checker(Graphene::Color &color1, Graphene::Color &color2);
    virtual ~Checker() = default;

protected:
    Graphene::Color m_Color1;
    Graphene::Color m_Color2;
};

#endif // __TEXTURE_H__