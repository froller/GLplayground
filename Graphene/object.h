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
    fvec3 m_Rotation;
    fvec3 m_Scale;
    
public:
    Object() = default;
    virtual ~Object() = default;
};

#endif // __OBJECT_H__
