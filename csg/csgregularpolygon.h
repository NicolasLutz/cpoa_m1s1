#ifndef CSGREGULARPOLYGON_H
#define CSGREGULARPOLYGON_H

#include "csgprimitive.h"
#include <vector>

class CsgRegularPolygon : public CsgPrimitive
{
public:
    CsgRegularPolygon();
    CsgRegularPolygon(const CsgRegularPolygon &other);
    CsgRegularPolygon(unsigned int nb_vertices);
    virtual ~CsgRegularPolygon();

    //Accesseurs//
    const std::vector<Vec2f>& Vertices() const;

    //Opérateurs//
    CsgRegularPolygon& operator++();
    CsgRegularPolygon& operator++(int);

    //Opérations//
    bool isInside(const Vec2f &vertice) const;

private:
    std::vector<Vec2f> m_vertices;
};

#endif // CSGREGULARPOLYGON_H
