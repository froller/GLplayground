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
