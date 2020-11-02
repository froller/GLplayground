#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "graphene.h"

/*******************************************************************************
 * 
 * Graphene::Camera::Targeted
 * 
 ******************************************************************************/

class Graphene::Camera::Targeted : public Graphene::Camera
{
public:
    Targeted(const fvec3 position, const fvec3 target, const float aspectRatio, const float FOV);
    virtual ~Targeted() = default;
    virtual fmat4 view() const override;
};

/*******************************************************************************
 * 
 * Graphene::Camera::Free
 * 
 ******************************************************************************/

class Graphene::Camera::Free : public Graphene::Camera
{
    Free(const fvec3 position, const fvec3 direction, const float aspectRatio, const float FOV);
    virtual ~Free() = default;
    virtual fmat4 view() const override;
};

#endif // __CAMERA_H__
