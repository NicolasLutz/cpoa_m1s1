#ifndef CSGREGULARPOLYGON_H
#define CSGREGULARPOLYGON_H

#include "csgprimitive.h"
#include <vector>

class CsgRegularPolygon : public CsgPrimitive
{
public:
    CsgRegularPolygon();
    CsgRegularPolygon(const CsgRegularPolygon &other);
    CsgRegularPolygon(int nb_vertices);
    virtual ~CsgRegularPolygon();

    //Accesseurs//
    int Vertices() const;

    //Opérateurs//
    CsgRegularPolygon& operator++();
    CsgRegularPolygon& operator++(int);

    //Opérations//
    bool intersects(const Vec2f &vertice) const;

private:
    int m_vertices;
};

#endif // CSGREGULARPOLYGON_H
