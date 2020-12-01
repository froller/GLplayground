#include "graphene.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

fmat4 Graphene::Object::transform() const
{
    glm::fmat4 tm = glm::fmat4(1);
    tm = glm::scale(glm::fmat4(1), m_Scale) * tm;
    tm = glm::mat4_cast(m_Rotation) * tm;
    tm = glm::translate(glm::fmat4(1), m_Position) * tm;
    return tm;
}

fvec3 Graphene::Object::position() const
{
    return m_Position;
}

void Graphene::Object::position(const fvec3 position)
{
    m_Position = position;
}

fquat Graphene::Object::rotation() const
{
    return m_Rotation;
}

void Graphene::Object::rotation(const fquat rotation)
{
    m_Rotation = rotation;
#ifdef DEBUG
    glm::fvec3 e = glm::eulerAngles(m_Rotation) / (float)M_PI * 180.f;
    SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Object %p rotation %+f\u00B0 %+f\u00B0 %+f\u00B0", this, e.x, e.y, e.z);
#endif
}

fvec3 Graphene::Object::scale() const
{
    return m_Scale;
}

void Graphene::Object::scale(const fvec3 scale)
{
    m_Scale = scale;
}
