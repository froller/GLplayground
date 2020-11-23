#include "graphene.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/vector_angle.hpp>

fmat4 Graphene::Camera::view() const
{
    return glm::quatLookAt(m_Position, m_Rotation);
}

fmat4 Graphene::Camera::projection() const
{
    return glm::perspectiveFov(m_FOV, 1.f, 1.f / m_AspectRatio, 0.1f, 100.f);
}

void Graphene::Camera::orbit(const fvec3 angle)
{
    glm::fmat4 transY = glm::rotate(glm::mat4(), angle.y, {1, 0, 0});
    glm::fmat4 transX = glm::rotate(glm::mat4(), angle.x, {0, 1, 0});
    m_Position = glm::fvec3(transX * transY * glm::fvec4(m_Position, 0));
    //m_Rotation = glm::fvec4(-transX * -transY * m_Rotation); // FIXME поворот через кватернион
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
    m_Rotation = glm::angleAxis(glm::angle(m_Target, m_Position), glm::cross(m_Target, m_Position));
}

fmat4 Graphene::Camera::Targeted::view() const
{
    fmat4 view = glm::lookAt(m_Position, m_Target, {0, 1, 0}); // FIXME добавить правильное вращение
    return view;
}

void Graphene::Camera::Targeted::rotation(const fquat rotation)
{
    // Для направленной камеры вращение осуществляется через вращение вокруг цели
    fvec3 eye = m_Position - m_Target;
    eye = glm::fvec3(glm::mat4_cast(rotation) * fvec4(eye, 0));
}

void Graphene::Camera::Targeted::rotation (const float angle)
{
    m_Rotation = glm::angleAxis(angle, m_Target - m_Position);
}

void Graphene::Camera::Targeted::orbit (const fvec3 angle)
{
    glm::fmat4 transY = glm::rotate(glm::mat4(1), angle.y, {1, 0, 0});
    glm::fmat4 transX = glm::rotate(transY, angle.x, {0, 1, 0});
    m_Position = glm::fvec3(transX * transY * glm::fvec4(m_Position, 0)); 
}
