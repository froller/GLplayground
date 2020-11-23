#ifndef __GRAPHENE_TYPES_H__
#define __GRAPHENE_TYPES_H__

#ifdef WITH_GLM

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

typedef glm::fvec2 fvec2;
typedef glm::fvec3 fvec3;
typedef glm::fvec4 fvec4;
typedef glm::fmat4 fmat4;
typedef glm::uint uint;
typedef glm::fquat fquat;

#else
#   error GLM is required at this time
#endif // WITH_GLM

#endif // __GRAPHENE_TYPES_H__
