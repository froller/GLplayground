#include "graphene.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/vector_angle.hpp>

fmat4 Graphene::Camera::view() const
{
    return glm::lookAt(m_Position, {0, 0, 0}, {0, 1, 0});
}

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

fvec4 Graphene::Camera::rotation() const
{
    return m_Rotation;
}

void Graphene::Camera::rotation(const fvec4 rotation)
{
    m_Rotation = rotation;
}

void Graphene::Camera::orbit(const fvec3 angle)
{
    glm::fmat4 transY = glm::rotate(glm::mat4(), angle.y, {1, 0, 0});
    glm::fmat4 transX = glm::rotate(glm::mat4(), angle.x, {0, 1, 0});
    m_Position = glm::fvec3(transX * transY * glm::fvec4(m_Position, 0));
    m_Rotation = glm::fvec4(-transX * -transY * m_Rotation);
}

void Graphene::Camera::dolly(const float offset)
{
    m_Position += m_Position * offset / 5.f; // FIXME: это будет работать криво при камере смотрящей не в 0
}


/*******************************************************************************
 * 
 * Targeted
 * 
 ******************************************************************************/

Graphene::Camera::Targeted::Targeted (const fvec3 position, const fvec3 target, const float aspectRatio, const float FOV)
        : Camera(position, {0, 0, 0, 0}, aspectRatio, FOV), m_Target(target)
{
    m_Rotation = glm::fvec4(glm::normalize(target - position), 0);
}

fmat4 Graphene::Camera::Targeted::view() const
{
    fmat4 view = glm::lookAt(m_Position, m_Target, {0, 1, 0}); // FIXME добавить правильное вращение
    return view;
}

void Graphene::Camera::Targeted::rotation (const fvec4 rotation)
{
    m_Rotation = glm::rotate(glm::fmat4(), rotation.w, m_Target - m_Position) * m_Rotation;
}

void Graphene::Camera::Targeted::orbit (const fvec3 angle)
{
    glm::fmat4 transY = glm::rotate(glm::mat4(1), angle.y, {1, 0, 0});
    glm::fmat4 transX = glm::rotate(transY, angle.x, {0, 1, 0});
    m_Position = glm::fvec3(transX * transY * glm::fvec4(m_Position, 0)); 
}
