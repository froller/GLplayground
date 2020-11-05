#include "graphene.h"
#include <glm/gtc/matrix_transform.hpp>

/*******************************************************************************
 * 
 * Graphene::Light::Omni
 * 
 ******************************************************************************/

Graphene::Light::Omni::Omni(const fvec3 position, const Color color)
{
    m_Position = position;
    m_Color = fvec3(1);
}

fmat4 Graphene::Light::Omni::view() const
{
    return fmat4(1.f);
}

fmat4 Graphene::Light::Omni::projection() const
{
    return glm::perspectiveFov((float)M_2_PI, 1.f, 1.f, 0.0f, 100.f);
}

