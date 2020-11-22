#include "graphene.h"

#include <glm/gtc/matrix_transform.hpp>

fmat4 Graphene::Object::transform() const
{
    fmat4 tm = fmat4();
    tm = glm::scale(tm, m_Scale);
    tm = glm::rotate(tm, m_Rotation.w, glm::fvec3(m_Rotation.x, m_Rotation.y, m_Rotation.z));
    tm = glm::translate(tm, m_Position);
    return tm;
}
