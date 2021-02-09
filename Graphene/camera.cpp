#include "graphene.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/vector_angle.hpp>

float Graphene::Camera::aspectRatio() const
{
    return m_AspectRatio;
}

void Graphene::Camera::aspectRatio(const float aspectRatio)
{
    m_AspectRatio = aspectRatio;
}

fmat4 Graphene::Camera::view() const
{
    return glm::lookAt(m_Position, m_Position - m_Rotation * s_Base, m_Head);
}

fmat4 Graphene::Camera::projection() const
{
    return glm::perspectiveFov(m_FOV, 1.f, 1.f / m_AspectRatio, 0.1f, 100.f);
}

float Graphene::Camera::FOV() const
{
    return m_FOV;
}

void Graphene::Camera::FOV(const float angle)
{
    m_FOV = angle;
}

void Graphene::Camera::orbit(const fvec3 angle)
{
    rotate(angle);
}

void Graphene::Camera::rotate(const fvec3 angle)
{
    rotation(glm::angleAxis(angle.x, glm::angleAxis(angle.y, m_Head) * glm::fvec3(1, 0, 0)) * glm::angleAxis(angle.y, m_Head) * m_Rotation);
}

void Graphene::Camera::dolly(const float offset)
{
    glm::fvec3 direction = m_Rotation * s_Base;
    position(m_Position + direction * offset);
}

void Graphene::Camera::zoom(const float angle)
{
    if (m_FOV > -angle && m_FOV < M_PI - angle)
        m_FOV = m_FOV + angle;
}


/*******************************************************************************
 * 
 * Targeted
 * 
 ******************************************************************************/

Graphene::Camera::Targeted::Targeted (const fvec3 position, const fvec3 target, const float aspectRatio, const float FOV)
        : Camera(position, {0, 0, 0, 0}, aspectRatio, FOV), m_Target(target)
{
    m_Rotation = glm::quatLookAt(m_Target - m_Position, m_Head);
}

fmat4 Graphene::Camera::Targeted::view() const
{
    return glm::lookAt(m_Position, m_Target, m_Head); // FIXME добавить правильное вращение "головы"
}

void Graphene::Camera::Targeted::rotation(const fquat rotation)
{
    // Для направленной камеры вращение осуществляется через вращение вокруг цели
    // фактически rotation и orbit - это одно и то же
    Graphene::Camera::rotation(rotation);
    float distance = glm::length(m_Target - m_Position);
    glm::fvec3 direction = m_Rotation * s_Base;
    m_Position = m_Target + direction / glm::length(direction) * distance;
}

void Graphene::Camera::Targeted::orbit(const fvec3 angle)
{
    // Вектор направления из кватерниона вращения (поворот нормы Z текущим кватернионом вращения камеры)
    glm::fvec3 direction = m_Rotation * s_Base;
    // Поворот вектора направления вокруг вертикальной оси
    direction = glm::rotate(direction, angle.y, m_Head);
    // Горизонтальная ось (норма X развернутая в координаты камеры и повернутая вокруг вертикальной оси)
    glm::fvec3 xaxis = glm::rotate(m_Rotation * glm::fvec3(1, 0, 0), angle.y, m_Head);
    // Поворот вектора направления вокруг горизонтальной оси
    direction = glm::rotate(glm::fvec4(direction, 0), angle.x, xaxis);
    // Финальный кватернион вращения камеры из направления
    rotation(glm::quatLookAt(-direction, m_Head));
}

void Graphene::Camera::Targeted::rotate(const fvec3 angle)
{
    orbit(angle);
}
