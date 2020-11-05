#ifndef __LIGHT_H__
#define __LIGHT_H__

#include "graphene.h"

/*******************************************************************************
 * 
 * Graphene::Light::Omni
 * 
 ******************************************************************************/

class Graphene::Light::Omni : public Graphene::Light
{
public:
    Omni(const fvec3 position, const Color color);
    virtual ~Omni() = default;
    virtual fmat4 view() const override;
    virtual fmat4 projection() const override;
};

#endif // __LIGHT_H__
