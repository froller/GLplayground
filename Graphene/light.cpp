#include "graphene.h"
#include <glm/gtc/matrix_transform.hpp>

fmat4 Graphene::Light::view() const
{
    return fmat4(1.f);
}

fmat4 Graphene::Light::projection() const
{
    return glm::perspectiveFov((float)M_2_PI, 1.f, 1.f, 0.0f, 100.f);
}

size_t Graphene::Light::lightData(void *lightBuffer) const
{
    LightSource *tmp = (LightSource *)lightBuffer;
    tmp->position = m_Position;
    tmp->color = m_Color;
    return sizeof(LightSource);
}

/*******************************************************************************
 * 
 * Graphene::Light::Omni
 * 
 ******************************************************************************/

Graphene::Light::Omni::Omni(const fvec3 position, const Graphene::Color color)
{
    m_Position = position;
    m_Color = color;
}

