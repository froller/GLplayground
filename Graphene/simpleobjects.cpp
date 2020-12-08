#include "graphene.h"
#include <math.h>
#include <array>

#define VERTEX(x,y,z,nx,ny,nz,r,g,b) m_Vertices.push_back({fvec3(x, y, z), fvec3(nx, ny, nz), fvec3(r, g, b)})
#define ELEMENT(a,b,c) m_Primitives.push_back({a, b, c})

Graphene::SimpleObjects::Triangle::Triangle(const fvec3 position, const fquat rotation, const fvec3 scale) : Model(position, rotation, scale)
{
    VERTEX( 0.f,  1.f / sqrtf(3.f), 0.f,   0.f, 0.f, -1.f,   1.f, 1.f, 1.f);
    VERTEX(-0.5, -0.5 / sqrtf(3.f), 0.f,   0.f, 0.f, -1.f,   1.f, 1.f, 1.f);
    VERTEX( 0.5, -0.5 / sqrtf(3.f), 0.f,   0.f, 0.f, -1.f,   1.f, 1.f, 1.f);
    ELEMENT(0, 1, 2);
}

Graphene::SimpleObjects::Square::Square(const fvec3 position, const fquat rotation, const fvec3 scale) : Model(position, rotation, scale)
{
    VERTEX(-0.5, -0.5, 0.f,   0.f, 0.f, -1.f,   1.f, 1.f, 1.f);
    VERTEX(-0.5,  0.5, 0.f,   0.f, 0.f, -1.f,   1.f, 1.f, 1.f);
    VERTEX( 0.5,  0.5, 0.f,   0.f, 0.f, -1.f,   1.f, 1.f, 1.f);
    VERTEX( 0.5, -0.5, 0.f,   0.f, 0.f, -1.f,   1.f, 1.f, 1.f);
    ELEMENT(0, 2, 1);
    ELEMENT(0, 2, 3);
}

Graphene::SimpleObjects::Tetrahedron::Tetrahedron(const fvec3 position, const fquat rotation, const fvec3 scale) : Model(position, rotation, scale)
{
    VERTEX( 0.f,  sqrtf(6.f) / -12.f, -1.f / sqrtf(3.f),    0.f, -1.f / sqrtf(3.f),    0.f,                0.5, 0.9, 0.f); // передний
    VERTEX(-0.5,  sqrtf(6.f) / -12.f,  0.5 / sqrtf(3.f),    0.f, -1.f / sqrtf(3.f),    0.f,                0.5, 0.9, 0.f); // левый
    VERTEX( 0.5,  sqrtf(6.f) / -12.f,  0.5 / sqrtf(3.f),    0.f, -1.f / sqrtf(3.f),    0.f,                0.5, 0.9, 0.f); // правый

    VERTEX( 0.f,  sqrtf(6.f) / -12.f, -1.f / sqrtf(3.f),   -0.5,  sqrtf(6.f) /  12.f, -0.5 / sqrtf(3.f),   0.5, 0.9, 0.f); // передний
    VERTEX( 0.f,  1.f / sqrtf(3.f),    0.f,                -0.5,  sqrtf(6.f) /  12.f, -0.5 / sqrtf(3.f),   0.5, 0.9, 0.f); // верхний
    VERTEX(-0.5,  sqrtf(6.f) / -12.f,  0.5 / sqrtf(3.f),   -0.5,  sqrtf(6.f) /  12.f, -0.5 / sqrtf(3.f),   0.5, 0.9, 0.f); // левый

    VERTEX(-0.5,  sqrtf(6.f) / -12.f,  0.5 / sqrtf(3.f),    0.f,  sqrtf(6.f) /  12.f,  1.f / sqrtf(3.f),   0.5, 0.9, 0.f); // левый
    VERTEX( 0.f,  1.f / sqrtf(3.f),    0.f,                 0.f,  sqrtf(6.f) /  12.f,  1.f / sqrtf(3.f),   0.5, 0.9, 0.f); // верхний
    VERTEX( 0.5,  sqrtf(6.f) / -12.f,  0.5 / sqrtf(3.f),    0.f,  sqrtf(6.f) /  12.f,  1.f / sqrtf(3.f),   0.5, 0.9, 0.f); // правый
  
    VERTEX( 0.5,  sqrtf(6.f) / -12.f,  0.5 / sqrtf(3.f),    0.5,  sqrtf(6.f) /  12.f, -0.5 / sqrtf(3.f),   0.5, 0.9, 0.f); // правый
    VERTEX( 0.f,  1.f / sqrtf(3.f),    0.f,                 0.5,  sqrtf(6.f) /  12.f, -0.5 / sqrtf(3.f),   0.5, 0.9, 0.f); // верхний
    VERTEX( 0.f,  sqrtf(6.f) / -12.f, -1.f / sqrtf(3.f),    0.5,  sqrtf(6.f) /  12.f, -0.5 / sqrtf(3.f),   0.5, 0.9, 0.f); // передний
    
    ELEMENT(0, 1, 2);
    ELEMENT(3, 4, 5);
    ELEMENT(6, 7, 8);
    ELEMENT(9, 10, 11);
}

Graphene::SimpleObjects::Cube::Cube(const fvec3 position, const fquat rotation, const fvec3 scale) : Model(position, rotation, scale)
{
    // передняя
    VERTEX(-0.5, -0.5, -0.5,    0.f,  0.f, -1.f,   0.f, 0.5, 0.9); // л н п  0
    VERTEX(-0.5,  0.5, -0.5,    0.f,  0.f, -1.f,   0.f, 0.5, 0.9); // л в п  1
    VERTEX( 0.5, -0.5, -0.5,    0.f,  0.f, -1.f,   0.f, 0.5, 0.9); // п н п  2
    VERTEX( 0.5,  0.5, -0.5,    0.f,  0.f, -1.f,   0.f, 0.5, 0.9); // п в п  3
    ELEMENT(2, 1, 0);
    ELEMENT(1, 2, 3);

    // задняя
    VERTEX(-0.5, -0.5,  0.5,    0.f,  0.f,  1.f,   0.f, 0.5, 0.9); // л н з  4
    VERTEX(-0.5,  0.5,  0.5,    0.f,  0.f,  1.f,   0.f, 0.5, 0.9); // л в з  5
    VERTEX( 0.5, -0.5,  0.5,    0.f,  0.f,  1.f,   0.f, 0.5, 0.9); // п н з  6
    VERTEX( 0.5,  0.5,  0.5,    0.f,  0.f,  1.f,   0.f, 0.5, 0.9); // п в з  7
    ELEMENT(5, 6, 4);
    ELEMENT(6, 5, 7);

    // левая
    VERTEX(-0.5, -0.5, -0.5,   -1.f,  0.f,  0.f,   0.f, 0.5, 0.9); // л н п  8
    VERTEX(-0.5,  0.5, -0.5,   -1.f,  0.f,  0.f,   0.f, 0.5, 0.9); // л в п  9
    VERTEX(-0.5, -0.5,  0.5,   -1.f,  0.f,  0.f,   0.f, 0.5, 0.9); // л н з  10
    VERTEX(-0.5,  0.5,  0.5,   -1.f,  0.f,  0.f,   0.f, 0.5, 0.9); // л в з  11
    ELEMENT(9, 10, 8);
    ELEMENT(10, 9, 11);

    // правая
    VERTEX( 0.5, -0.5, -0.5,    1.f,  0.f,  0.f,   0.f, 0.5, 0.9); // п н п  12
    VERTEX( 0.5,  0.5, -0.5,    1.f,  0.f,  0.f,   0.f, 0.5, 0.9); // п в п  13
    VERTEX( 0.5, -0.5,  0.5,    1.f,  0.f,  0.f,   0.f, 0.5, 0.9); // п н з  14
    VERTEX( 0.5,  0.5,  0.5,    1.f,  0.f,  0.f,   0.f, 0.5, 0.9); // п в з  15
    ELEMENT(14, 13, 12);
    ELEMENT(13, 14, 15);

    // верхняя
    VERTEX(-0.5,  0.5, -0.5,    0.f,  1.f,  0.f,   0.f, 0.5, 0.9); // л в п  16
    VERTEX( 0.5,  0.5, -0.5,    0.f,  1.f,  0.f,   0.f, 0.5, 0.9); // п в п  17
    VERTEX(-0.5,  0.5,  0.5,    0.f,  1.f,  0.f,   0.f, 0.5, 0.9); // л в з  18
    VERTEX( 0.5,  0.5,  0.5,    0.f,  1.f,  0.f,   0.f, 0.5, 0.9); // п в з  19
    ELEMENT(17, 18, 16);
    ELEMENT(18, 17, 19);

    // нижняя
    VERTEX(-0.5, -0.5, -0.5,    0.f, -1.f,  0.f,   0.f, 0.5, 0.9); // л н п  20
    VERTEX( 0.5, -0.5, -0.5,    0.f, -1.f,  0.f,   0.f, 0.5, 0.9); // п н п  21
    VERTEX(-0.5, -0.5,  0.5,    0.f, -1.f,  0.f,   0.f, 0.5, 0.9); // л н з  22
    VERTEX( 0.5, -0.5,  0.5,    0.f, -1.f,  0.f,   0.f, 0.5, 0.9); // п н з  23
    ELEMENT(22, 21, 20);
    ELEMENT(21, 22, 23);
}

/*
Graphene::SimpleObjects::Sphere::Sphere(const fvec3 position, const fquat rotation, const fvec3 scale) : Model(position, rotation, scale)
{
    VERTEX(sqrtf(2.f) / -2.f, 0.f, sqrtf(2.f) /  2.f, sqrtf(2.f) / -2.f, 0.f, sqrtf(2.f) /  2.f, 0.9, 0.5, 0.f); // л з 0
    VERTEX(sqrtf(2.f) /  2.f, 0.f, sqrtf(2.f) /  2.f, sqrtf(2.f) /  2.f, 0.f, sqrtf(2.f) /  2.f, 0.9, 0.5, 0.f); // п з 1
    VERTEX(sqrtf(2.f) /  2.f, 0.f, sqrtf(2.f) / -2.f, sqrtf(2.f) /  2.f, 0.f, sqrtf(2.f) / -2.f, 0.9, 0.5, 0.f); // п п 2
    VERTEX(sqrtf(2.f) / -2.f, 0.f, sqrtf(2.f) / -2.f, sqrtf(2.f) / -2.f, 0.f, sqrtf(2.f) / -2.f, 0.9, 0.5, 0.f); // л п 3
    VERTEX(0.f, sqrtf(2.f) /  2.f, 0.f, 0.f, sqrtf(2.f) /  2.f, 0.f, 0.9, 0.5, 0.0); // в 4
    VERTEX(0.f, sqrtf(2.f) / -2.f, 0.f, 0.f, sqrtf(2.f) / -2.f, 0.f, 0.9, 0.5, 0.0); // н 5
    ELEMENT(1, 0, 4);
    ELEMENT(2, 1, 4);
    ELEMENT(3, 2, 4);
    ELEMENT(0, 3, 4);
    ELEMENT(0, 1, 5);
    ELEMENT(1, 2, 5);
    ELEMENT(2, 3, 5);
    ELEMENT(3, 0, 5);
}
*/

#include <glm/gtc/quaternion.hpp>
#include <glm/ext/quaternion_exponential.hpp>

Graphene::SimpleObjects::UVSphere::UVSphere(const fvec3 position, const fquat rotation, const fvec3 scale) : Model(position, rotation, scale)
{
    int vertexAcc = 0;
    std::vector<Vertex> lowerVertices;
    for (int lat = -(int)s_Segments / 2; lat <= (int)s_Segments / 2; ++lat)   // Проходим половину параллелей (вторая половина идентична, с точностью до знака Y)
    {
        // Число меридианов (вершин) на данной широте
        int meridians = 2 * s_Segments;  // Число меридианов
        float meridianStep = 2.f * M_PI / meridians;  // Угол между меридианами
        float meridianOffset = 0.f;  // Смещение "нулевого" меридиана

        // Создание вершин параллели
        std::vector<Vertex> vertices;
        for (int lon = 0; lon < meridians; ++lon)  // Проходим все меридианы
        {
            // Нормаль азимута
            glm::fvec3 nor =
                glm::angleAxis(meridianStep * (float)lon + meridianOffset, glm::fvec3(0, 1, 0)) // Азимут
                * glm::fvec3(0, 0, 1);  // Норма Z
            // Координаты вершины
            glm::fvec3 vertexCoords =
                glm::angleAxis((float)M_PI / s_Segments * -lat, nor)   // Угол места
                * glm::angleAxis(meridianStep * (float)lon + meridianOffset, glm::fvec3(0, 1, 0))   // Азимут
                * glm::fvec3(1, 0, 0);  // Норма X

            // Вершина северного полушария
            Vertex vertex = {vertexCoords, -vertexCoords, (vertexCoords + glm::fvec3(1, 1, 1)) / 2.f };
            vertices.push_back(vertex);
            m_Vertices.push_back(vertex); // Добавляем вершину в вертексный буфер
            ++vertexAcc;

            if (abs(lat) == s_Segments / 2)  // полюс
                break;
        }
        
        // Связывание вершин параллели с вершинами нижних широт
        for (int lon = 0; lon < std::max(vertices.size(), lowerVertices.size()) && lowerVertices.size() > 0; ++lon)
        {
            int lowerIdxC = vertexAcc - vertices.size() - lowerVertices.size() + lon;    // текущий
            while (lowerIdxC >= vertexAcc - vertices.size()) // закольцовывание
                lowerIdxC -= lowerVertices.size();
            int lowerIdxR = lowerIdxC + 1;  // правый
            while (lowerIdxR >= vertexAcc - vertices.size()) // закольцовывание
                lowerIdxR -= lowerVertices.size();
            int currentIdxC = (int)vertexAcc - vertices.size() + lon; // текущий
            while (currentIdxC >= vertexAcc) // закольцовывание
                currentIdxC -= vertices.size();
            int currentIdxR = currentIdxC + 1; // правый
            while (currentIdxR >= vertexAcc) // закольцовывание
                currentIdxR -= vertices.size();

            if (currentIdxR != currentIdxC)
                m_Primitives.push_back({ (unsigned int)lowerIdxC, (unsigned int)currentIdxR, (unsigned int)currentIdxC });
            if (lowerIdxR != lowerIdxC)
                m_Primitives.push_back({ (unsigned int)lowerIdxC, (unsigned int)lowerIdxR, (unsigned int)currentIdxR });
        }

        lowerVertices = vertices;
    }
    
    
}



#undef ELEMENT
#undef VERTEX

