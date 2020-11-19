#ifndef __LIGHT_H__
#define __LIGHT_H__

/*******************************************************************************
 * 
 * Graphene::Light
 * 
 ******************************************************************************/

class Graphene::Light : public Graphene::Object
{
public:
    class Omni;
public:
    fvec3 m_Color;
    float m_Attenuation = -1.f;
public:
    Light() = default;
    virtual ~Light() = default;
    virtual fmat4 view() const;
    virtual fmat4 projection() const;
    virtual size_t lightData(void *lightBuffer) const;
    virtual float attenuation() const;
    virtual void attenuation(const float distance);
};

/*******************************************************************************
 * 
 * Graphene::Light::Omni
 * 
 ******************************************************************************/

class Graphene::Light::Omni : public Graphene::Light
{
public:
    Omni(const fvec3 position, const Graphene::Color color);
};

#endif // __LIGHT_H__
