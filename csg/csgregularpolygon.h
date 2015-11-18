#ifndef CSGREGULARPOLYGON_H
#define CSGREGULARPOLYGON_H

#include "csgprimitive.h"
#include <vector>

class CsgRegularPolygon : public CsgPrimitive
{
public:
    CsgRegularPolygon();
    CsgRegularPolygon(Point origin);
    CsgRegularPolygon(const CsgRegularPolygon &other);
    virtual ~CsgRegularPolygon();

    //Accesseurs//
    const std::vector<Point>& getPoints() const;

    //Operateurs//
    CsgRegularPolygon& operator++();
    CsgRegularPolygon& operator++(int);

private:
    std::vector<Point> m_points;
};

#endif // CSGREGULARPOLYGON_H
