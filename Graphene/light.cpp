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
    tmp->attenuation = m_Attenuation;
    return sizeof(LightSource);
}

float Graphene::Light::attenuation() const
{
    return m_Attenuation;
}

void Graphene::Light::attenuation(const float distance)
{
    m_Attenuation = distance;
}
