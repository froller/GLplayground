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
};

/*******************************************************************************
 * 
 * Graphene::SimpleObjects::Triangle
 * 
 ******************************************************************************/

class Graphene::SimpleObjects::Triangle : public Graphene::Model
{
public:
    Triangle(const fvec3 position = { 0, 0, 0 }, const fvec3 rotation = { 0, 0, 0 }, const fvec3 scale = { 1, 1, 1 });
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
    Square(const fvec3 position = {0, 0, 0}, const fvec3 rotation = {0, 0, 0}, const fvec3 scale = {1, 1, 1});
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
    Tetrahedron(const fvec3 position = {0, 0, 0}, const fvec3 rotation = {0, 0, 0}, const fvec3 scale = {1, 1, 1});
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
    Cube(const fvec3 position = { 0, 0, 0 }, const fvec3 rotation = { 0, 0, 0 }, const fvec3 scale = { 1, 1, 1 });
    virtual ~Cube() = default;
};

/*******************************************************************************
 * 
 * Graphene::SimpleObjects::Sphere
 * 
 ******************************************************************************/

class Graphene::SimpleObjects::Sphere : public Graphene::Model
{
    Sphere() = default;
    virtual ~Sphere() = default;
};

#endif // __SIMPLEOBJECTS_H__
