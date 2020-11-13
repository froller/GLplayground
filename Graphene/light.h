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
    Omni(const fvec3 position, const Graphene::Color color);
};

#endif // __LIGHT_H__
