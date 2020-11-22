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
    Camera(const fvec3 position = {0, 0, 2}, const fvec4 rotation = {0, 0, 0, 0}, const float aspectRatio = 1.25, const float FOV = M_PI_4)
        : Object(position, rotation), m_AspectRatio(aspectRatio), m_FOV(FOV) {};
    virtual ~Camera() = default;
    virtual fmat4 view() const;
    virtual fmat4 projection() const;
    virtual fvec3 position() const;
    virtual void position(const fvec3 position);
    virtual fvec4 rotation() const;
    virtual void rotation(const fvec4 rotation);
    virtual void orbit(const fvec3 angle);
    virtual void dolly(const float offset);
};

/*******************************************************************************
 * 
 * Graphene::Camera::Targeted
 * 
 ******************************************************************************/

class Graphene::Camera::Targeted : public Graphene::Camera
{
protected:
    fvec3 m_Target;
public:
    Targeted(const fvec3 position = {0, 0, 2}, const fvec3 target = {0, 0, 0}, const float aspectRatio = 1.25, const float FOV = M_PI_4);
    virtual ~Targeted() = default;
    virtual fmat4 view() const override;
    virtual void rotation(const fvec4 rotation) override;
    virtual void orbit(const fvec3 angle) override;
};

#endif // __CAMERA_H__
