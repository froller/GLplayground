#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "graphene.h"

class Graphene::Camera::Targeted : public Graphene::Camera
{
public:
    Targeted(const fvec3 position, const fvec3 target, const float aspectRatio, const float FOV);
    virtual ~Targeted() = default;
    virtual const fmat4 view() const override;
};

class Graphene::Camera::Free : public Graphene::Camera
{
    Free(const fvec3 position, const fvec3 direction, const float aspectRatio, const float FOV);
    virtual ~Free() = default;
    virtual const fmat4 view() const override;
};

#endif // __CAMERA_H__
