#ifndef __SIMPLEOBJECTS_H__
#define __SIMPLEOBJECTS_H__

/*******************************************************************************
 * 
 * Graphene::SimpleObjects
 * 
 ******************************************************************************/

class Graphene::SimpleObjects
{
public:
    class Triangle;
    class Square;
    class Tetrahedron;
    class Cube;
    class Sphere;
    class UVSphere;
};

/*******************************************************************************
 * 
 * Graphene::SimpleObjects::Triangle
 * 
 ******************************************************************************/

class Graphene::SimpleObjects::Triangle : public Graphene::Model
{
public:
    Triangle(const fvec3 position = { 0, 0, 0 }, const fquat rotation = { 0, 0, 0, 1 }, const fvec3 scale = { 1, 1, 1 });
    virtual ~Triangle() = default;
};

/*******************************************************************************
 * 
 * Graphene::SimpleObjects::Square
 * 
 ******************************************************************************/

class Graphene::SimpleObjects::Square : public Graphene::Model
{
public:
    Square(const fvec3 position = { 0, 0, 0 }, const fquat rotation = { 0, 0, 0, 1 }, const fvec3 scale = { 1, 1, 1 });
    virtual ~Square() = default;
};

/*******************************************************************************
 * 
 * Graphene::SimpleObjects::Tetrahedron
 * 
 ******************************************************************************/

class Graphene::SimpleObjects::Tetrahedron : public Graphene::Model
{
public:
    Tetrahedron(const fvec3 position = { 0, 0, 0 }, const fquat rotation = { 0, 0, 0, 1 }, const fvec3 scale = { 1, 1, 1 });
    virtual ~Tetrahedron() = default;
};

/*******************************************************************************
 * 
 * Graphene::SimpleObjects::Cube
 * 
 ******************************************************************************/

class Graphene::SimpleObjects::Cube : public Graphene::Model
{
public:
    Cube(const fvec3 position = { 0, 0, 0 }, const fquat rotation = { 0, 0, 0, 1 }, const fvec3 scale = { 1, 1, 1 });
    virtual ~Cube() = default;
};

/*******************************************************************************
 * 
 * Graphene::SimpleObjects::UVSphere
 * 
 ******************************************************************************/

class Graphene::SimpleObjects::UVSphere : public Graphene::Model
{
protected:
    static constexpr unsigned int s_Segments = 8;
public:
    UVSphere(const fvec3 position = { 0, 0, 0 }, const fquat rotation = { 0, 0, 0, 1 }, const fvec3 scale = { 1, 1, 1 });
    virtual ~UVSphere() = default;
};

#endif // __SIMPLEOBJECTS_H__
