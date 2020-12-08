#include "graphene.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

fmat4 Graphene::Object::transform() const
{
    glm::fmat4 tm = glm::translate(glm::fmat4(1), m_Position) * glm::mat4_cast(m_Rotation) *glm::scale(glm::fmat4(1), m_Scale);
    SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Transform matrix for %p\n\t%f\t%f\t%f\t%f\n\t%f\t%f\t%f\t%f\n\t%f\t%f\t%f\t%f\n\t%f\t%f\t%f\t%f",
        this,
        tm[0][0], tm[1][0], tm[2][0], tm[3][0],
        tm[0][1], tm[1][1], tm[2][1], tm[3][1],
        tm[0][2], tm[1][2], tm[2][2], tm[3][2],
        tm[0][3], tm[1][3], tm[2][3], tm[3][3]
    );
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
}

fvec3 Graphene::Object::scale() const
{
    return m_Scale;
}

void Graphene::Object::scale(const fvec3 scale)
{
    m_Scale = scale;
}
