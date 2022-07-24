#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include <list>

class Graphene::Texture
{
public:
    class Value;
    class Color;
    class Checker;
    enum class Type {
        None = 0,
        Value,
        Color,
        Checker
    };
    
#pragma pack(push, 8)
    struct RGB8 {
        uint8_t r, g, b;
    };
    struct RGBA8 {
        uint8_t r, g, b, a;
    };
#pragma pack(pop)
    
    constexpr static const Type s_Type = Type::None;
    constexpr static const Type type() { return s_Type; };

public:
    Texture();
    virtual ~Texture();
    constexpr size_t width() const { return m_Width; }
    constexpr size_t height() const { return m_Height; }
    constexpr void *buffer() const { return m_Buffer; }
    constexpr GLuint textureID() const { return m_TextureID; }
    constexpr GLuint textureUnit() const { return m_TextureUnit; }
    static inline std::shared_ptr<Value> FlatWhite() {
        if (!s_FlatWhite)
            s_FlatWhite = std::make_shared<Value>(1.f);
        return s_FlatWhite;
    };
    static inline std::shared_ptr<Value> FlatGray() {
        if (!s_FlatGray)
            s_FlatGray = std::make_shared<Value>(0.5);
        return s_FlatGray;
    };
    static inline std::shared_ptr<Value> FlatBlack() {
        if (!s_FlatBlack)
            s_FlatBlack = std::make_shared<Value>(0.f);
        return s_FlatBlack;
    };

protected:
    size_t m_Width = 0;
    size_t m_Height = 0;
    GLuint m_TextureID = 0;
    GLuint m_TextureUnit = 0;
    void *m_Buffer = nullptr;

private:    
    static std::shared_ptr<Value> s_FlatWhite;
    static std::shared_ptr<Value> s_FlatGray;
    static std::shared_ptr<Value> s_FlatBlack;
};

class Graphene::Texture::Value : public Graphene::Texture
{
public:
    constexpr static const Type s_Type = Type::Value;
    constexpr static const Type type() { return s_Type; };
protected:
    constexpr static const GLenum s_GLTextureType = GL_TEXTURE_2D;
    constexpr static const GLenum s_GLPixelFormat = GL_RGB8;

public:
    Value(const float &value);
    virtual ~Value() = default;

protected:
    float m_Value;
};

class Graphene::Texture::Color : public Graphene::Texture
{
public:
    constexpr static const Type s_Type = Type::Color;
    constexpr static const Type type() { return s_Type; };
protected:
    constexpr static const GLenum s_GLTextureType = GL_TEXTURE_2D;
    constexpr static const GLenum s_GLPixelFormat = GL_RGB8;

public:
    Color(const Graphene::Color &color);
    virtual ~Color() = default;

protected:
    Graphene::Color m_Color;
};

class Graphene::Texture::Checker : public Graphene::Texture
{
public:
    constexpr static const Type s_Type = Type::Checker;
    constexpr static const Type type() { return s_Type; };
protected:
    constexpr static const GLenum s_GLTextureType = GL_TEXTURE_2D;
    constexpr static const GLenum s_GLPixelFormat = GL_RGB8;

public:
    Checker(const Graphene::Color &color1, const Graphene::Color &color2);
    virtual ~Checker() = default;

protected:
    Graphene::Color m_Color1;
    Graphene::Color m_Color2;
};

#endif // __TEXTURE_H__
