#include "graphene.h"
#include <glm/gtc/matrix_transform.hpp>

const fmat4 Graphene::Camera::projection() const
{
    return glm::perspectiveFov(m_FOV, 1.f, 1.f / m_AspectRatio, 0.1f, 100.f);
}

/*******************************************************************************
 * 
 * Targeted
 * 
 ******************************************************************************/

Graphene::Camera::Targeted::Targeted(const fvec3 position, const fvec3 target, const float aspectRatio, const float FOV)
{
    m_Position = position;
    m_Scale = fvec3(1);
    m_Rotation = target - m_Position;
    m_AspectRatio = aspectRatio;
    m_FOV = FOV;
}

const fmat4 Graphene::Camera::Targeted::view() const
{
    // Directional camera has rotation not target
    // "head" vector is hardcoded to [0, 1, 0] for now
    return glm::lookAt(m_Position, m_Rotation - m_Position, fvec3(0, 1, 0));
}

/*******************************************************************************
 * 
 * Free
 * 
 ******************************************************************************/

Graphene::Camera::Free::Free(const fvec3 position, const fvec3 direction, const float aspectRatio, const float FOV)
{
    m_Position = position;
    m_Scale = fvec3(1);
    m_Rotation = direction + m_Position;
    m_AspectRatio = aspectRatio;
    m_FOV = FOV;
}

const fmat4 Graphene::Camera::Free::view() const
{
    // Directional camera has rotation not target
    // "head" vector is hardcoded to [0, 1, 0] for now
    return glm::lookAt(m_Position, m_Rotation - m_Position, fvec3(0, 1, 0));
}
