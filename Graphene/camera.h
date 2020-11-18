#ifndef __CAMERA_H__
#define __CAMERA_H__

/*******************************************************************************
 * 
 * Graphene::Camera
 * 
 ******************************************************************************/

class Graphene::Camera : public Graphene::Object
{
public:
    class Free;
    class Targeted;
public:
    float m_AspectRatio;
    float m_FOV;
public:
    Camera() = default;
    virtual ~Camera() = default;
    virtual fmat4 view() const = 0;
    virtual fmat4 projection() const;
    virtual fvec3 position() const;
    virtual void position(const fvec3 position);
    virtual void orbit(const fvec3 angle);
};

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
