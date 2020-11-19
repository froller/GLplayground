#include "graphene.h"
#include <glm/gtc/matrix_transform.hpp>

fmat4 Graphene::Camera::projection() const
{
    return glm::perspectiveFov(m_FOV, 1.f, 1.f / m_AspectRatio, 0.1f, 100.f);
}

fvec3 Graphene::Camera::position() const
{
    return m_Position;
}

void Graphene::Camera::position(const fvec3 position)
{
    m_Position = position;
}

void Graphene::Camera::orbit(const fvec3 angle)
{
    glm::fmat4 transY = glm::rotate(glm::mat4(1.f), angle.y, glm::fvec3(1, 0, 0));
    glm::fmat4 transX = glm::rotate(transY, angle.x, glm::fvec3(0, 1, 0));
    m_Position = glm::fvec3(transX * transY * glm::fvec4(m_Position, 0));
    m_Rotation = glm::fvec3(-transX * -transY * glm::fvec4(m_Rotation, 0));
}

void Graphene::Camera::dolly(const float offset)
{
    m_Position += m_Position * offset / 5.f;
}


/*******************************************************************************
 * 
 * Targeted
 * 
 ******************************************************************************/

Graphene::Camera::Targeted::Targeted(const fvec3 position, const fvec3 target, const float aspectRatio, const float FOV)
{
    //m_Position = fvec3(0, 0, 2);
    m_Position = position;
    m_Scale = fvec3(1);
    //m_Rotation = fvec3(0, 0, -1);
    m_Rotation =  target - m_Position;
    m_AspectRatio = aspectRatio;
    m_FOV = FOV;
}

fmat4 Graphene::Camera::Targeted::view() const
{
    // Directional camera has rotation not target
    // "head" vector is hardcoded to [0, 1, 0] for now
    //return glm::lookAt(fvec3(1, 1, 1), fvec3(0, 0, 0), fvec3(0, 1, 0));
    fmat4 view = glm::lookAt(m_Position, m_Rotation + m_Position, fvec3(0, 1, 0));
    //return glm::inverse(view);
    return view;
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
    m_Rotation = direction;
    m_AspectRatio = aspectRatio;
    m_FOV = FOV;
}

fmat4 Graphene::Camera::Free::view() const
{
    // Directional camera has rotation not target
    // "head" vector is hardcoded to [0, 1, 0] for now
    return glm::lookAt(m_Position, m_Rotation + m_Position, fvec3(0, 1, 0));
}
