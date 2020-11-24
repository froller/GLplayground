#ifndef __OBJECT_H__
#define __OBJECT_H__

/*******************************************************************************
 * 
 * Graphene::Object
 * 
 ******************************************************************************/

class Graphene::Object
{
protected:
    fvec3 m_Position;
    fquat m_Rotation;
    fvec3 m_Scale;
    
public:
    Object(const fvec3 position = { 0, 0, 0 }, const fquat rotation = { 0, 0, 0, 1 }, const fvec3 scale = { 1, 1, 1 })
        : m_Position(position), m_Rotation(rotation), m_Scale(scale) {};
    virtual ~Object() = default;
    virtual fvec3 position() const;
    virtual void position(const fvec3 position);
    virtual fquat rotation() const;
    virtual void rotation(const fquat rotation);
    virtual fvec3 scale() const;
    virtual void scale(const fvec3 scale);
    virtual fmat4 transform() const;
};

#endif // __OBJECT_H__
