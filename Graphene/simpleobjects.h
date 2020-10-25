#ifndef __SIMPLEOBJECTS_H__
#define __SIMPLEOBJECTS_H__

#include "graphene.h"

class Graphene::SimpleObjects::Triangle : public Graphene::Model
{
public:
    Triangle();
    virtual ~Triangle() = default;
};

class Graphene::SimpleObjects::Square : public Graphene::Model
{
public:
    Square() = default;
    virtual ~Square() = default;
};

class Graphene::SimpleObjects::Tetrahedron : public Graphene::Model
{
public:
    Tetrahedron() = default;
    virtual ~Tetrahedron() = default;
};

class Graphene::SimpleObjects::Cube : public Graphene::Model
{
    Cube() = default;
    virtual ~Cube() = default;
};

class Graphene::SimpleObjects::Sphere : public Graphene::Model
{
    Sphere() = default;
    virtual ~Sphere() = default;
};

#endif // __SIMPLEOBJECTS_H__
