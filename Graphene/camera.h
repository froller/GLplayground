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
    class Targeted;
protected:
    float m_AspectRatio;
    float m_FOV;
    fvec3 m_Head = { 0, 1, 0 };
    static constexpr fvec3 s_Base = glm::fvec3( 0, 0, 1 );
public:
    Camera(const fvec3 position = {0, 0, 2}, const fquat rotation = {0, 0, 0, 0}, const float aspectRatio = 1.25, const float FOV = M_PI_4)
        : Object(position, rotation), m_AspectRatio(aspectRatio), m_FOV(FOV) {};
    virtual ~Camera() = default;
    virtual fmat4 view() const;
    virtual fmat4 projection() const;
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
    virtual void rotation(const fquat rotation) override;
    virtual void rotation(const float angle);
    virtual void orbit(const fvec3 angle) override;
    virtual void dolly(const float offset) override;
};

#endif // __CAMERA_H__
