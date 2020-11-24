#include "graphene.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/vector_angle.hpp>

fmat4 Graphene::Camera::view() const
{
    return glm::lookAt(m_Position, glm::fvec3(m_Rotation * glm::fvec4(s_Base, 0)) * -1.f, m_Head);
}

fmat4 Graphene::Camera::projection() const
{
    return glm::perspectiveFov(m_FOV, 1.f, 1.f / m_AspectRatio, 0.1f, 100.f);
}

void Graphene::Camera::orbit(const fvec3 angle)
{
    // Orbit для свободной камеры выглядит бесполезным
    rotation(glm::angleAxis(angle.y, glm::fvec3(1, 0, 0)) * glm::angleAxis(angle.x, glm::fvec3(0, 1, 0)));
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
    m_Rotation = rotation;
    float distance = glm::length(m_Target - m_Position);
    fvec3 direction = m_Rotation * glm::fvec4(s_Base, 0);
    m_Position = m_Target + direction / glm::length(direction) * distance;
}

void Graphene::Camera::Targeted::rotation (const float angle)
{
    // Для вращение без изменения положения и цели остается только одна степень свободы
    // вращение вокруг оптической оси камеры
    m_Rotation = glm::angleAxis(angle, m_Target - m_Position);
}

void Graphene::Camera::Targeted::orbit(const fvec3 angle)
{
    //SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "Orbitting to %+f° %+f°", angle.x, angle.y);
    rotation(
        glm::angleAxis(angle.y, glm::fvec3(1, 0, 0))
        * glm::angleAxis(angle.x, glm::fvec3(glm::fvec4(0, 1, 0, 0)))
        * m_Rotation
    );
}

void Graphene::Camera::Targeted::dolly(const float offset)
{
    glm::fvec3 directrion = m_Position - m_Target;
    if (glm::length(directrion) > 0.1 || offset > 0) // Здесь бы неплохо было использовать минимальную и максимальную дальность отрисовки
        m_Position += glm::normalize(directrion) * offset;
}
