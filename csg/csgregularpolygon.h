#ifndef CSGREGULARPOLYGON_H
#define CSGREGULARPOLYGON_H

#include "csgprimitive.h"
#include <vector>

class CsgRegularPolygon : public CsgPrimitive
{
public:
    CsgRegularPolygon();
    CsgRegularPolygon(Vec2f origin);
    CsgRegularPolygon(const CsgRegularPolygon &other);
    virtual ~CsgRegularPolygon();

    //Accesseurs//
    const std::vector<Vec2f>& Vertices() const;

    //Operateurs//
    CsgRegularPolygon& operator++();
    CsgRegularPolygon& operator++(int);

private:
    std::vector<Vec2f> m_vertices;
};

#endif // CSGREGULARPOLYGON_H
