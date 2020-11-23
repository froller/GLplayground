#ifndef __OBJECT_H__
#define __OBJECT_H__

/*******************************************************************************
 * 
 * Graphene::Object
 * 
 ******************************************************************************/

class Graphene::Object
{
public:
    fvec3 m_Position;
    fquat m_Rotation;
    fvec3 m_Scale;
    
public:
    Object(const fvec3 position = { 0, 0, 0 }, const fquat rotation = { 0, 0, 0, 1 }, const fvec3 scale = { 1, 1, 1 })
        : m_Position(position), m_Rotation(rotation), m_Scale(scale) {};
    virtual ~Object() = default;
    virtual fmat4 transform() const;
};

#endif // __OBJECT_H__
