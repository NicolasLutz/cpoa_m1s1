#include "csgregularpolygon.h"

CsgRegularPolygon::CsgRegularPolygon() : CsgPrimitive(), m_points(3)
{}

//----------------------------------------------------------------------------

CsgRegularPolygon::CsgRegularPolygon(Point origin) : CsgPrimitive(origin)
{}

//----------------------------------------------------------------------------

CsgRegularPolygon::CsgRegularPolygon(const CsgRegularPolygon &other) : CsgPrimitive(other), m_points(other.getPoints())
{}

//----------------------------------------------------------------------------

CsgRegularPolygon::~CsgRegularPolygon()
{}

//----------------------------------------------------------------------------
//Accesseurs//

const std::vector<Point>& CsgRegularPolygon::getPoints() const
{
    return m_points;
}

CsgRegularPolygon& CsgRegularPolygon::operator++()
{
    return *this;
}

CsgRegularPolygon& CsgRegularPolygon::operator++(int)
{
    return ++(*this);
}
