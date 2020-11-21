#ifndef __GRAPHENE_TYPES_H__
#define __GRAPHENE_TYPES_H__

#ifdef WITH_GLM

#include <glm/glm.hpp>

typedef glm::fvec2 fvec2;
typedef glm::fvec3 fvec3;
typedef glm::fmat4 fmat4;
typedef glm::uint uint;

#else

typedef struct {float x; float y} fvec2;
typedef struct {float x; float y; float z} fvec3;
typedef struct {float x; float y; float z; float w} fvec4;
typedef struct {fvec4 x; fvec4 y; fvec4 z; fvec4 w} fmat4;

#endif // WITH_GLM

#endif // __GRAPHENE_TYPES_H__
