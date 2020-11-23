#include "graphene.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/vector_angle.hpp>

fmat4 Graphene::Camera::view() const
{
    return glm::mat4_cast(m_Rotation);
}

fmat4 Graphene::Camera::projection() const
{
    return glm::perspectiveFov(m_FOV, 1.f, 1.f / m_AspectRatio, 0.1f, 100.f);
}

void Graphene::Camera::orbit(const fvec3 angle)
{
    // Orbit для свободной камеры выглядит бесполезным, т.к. вращает ее вокруг центра мира
    m_Rotation = glm::angleAxis(angle.y, glm::fvec3(1, 0, 0)) * glm::angleAxis(angle.x, glm::fvec3(0, 1, 0));
    m_Position = glm::angleAxis(angle.y, glm::fvec3(1, 0, 0)) * glm::angleAxis(angle.x, glm::fvec3(0, 1, 0)) * m_Position;
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
    fmat4 view = glm::lookAt(m_Position, m_Target, m_Head); // FIXME добавить правильное вращение "головы"
    return view;
}

void Graphene::Camera::Targeted::rotation(const fquat rotation)
{
    // Для направленной камеры вращение осуществляется через вращение вокруг цели
    // фактически rotation и orbit - это одно и то же
    m_Rotation = rotation;
    fvec3 eye = m_Position - m_Target;
    eye = glm::mat4_cast(m_Rotation) * fvec4(eye, 0);
    m_Position = m_Target + eye;
}

void Graphene::Camera::Targeted::rotation (const float angle)
{
    // Для вращение без изменения положения и цели остается только одна степень свободы
    // вращение вокруг оптической оси камеры
    m_Rotation = glm::angleAxis(angle, m_Target - m_Position);
}

void Graphene::Camera::Targeted::orbit(const fvec3 angle)
{
    rotation(glm::angleAxis(angle.y, glm::fvec3(1, 0, 0)) * glm::angleAxis(angle.x, glm::fvec3(0, 1, 0)));
}
