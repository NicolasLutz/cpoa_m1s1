#include "csgregularpolygon.h"

CsgRegularPolygon::CsgRegularPolygon() : CsgPrimitive(), m_vertices(3)
{}

//----------------------------------------------------------------------------

CsgRegularPolygon::CsgRegularPolygon(Vec2f origin) : CsgPrimitive(origin)
{}

//----------------------------------------------------------------------------

CsgRegularPolygon::CsgRegularPolygon(const CsgRegularPolygon &other) : CsgPrimitive(other), m_vertices(other.Vertices())
{}

//----------------------------------------------------------------------------

CsgRegularPolygon::~CsgRegularPolygon()
{}

//----------------------------------------------------------------------------
//Accesseurs//

const std::vector<Vec2f>& CsgRegularPolygon::Vertices() const
{
    return m_vertices;
}

CsgRegularPolygon& CsgRegularPolygon::operator++()
{
    return *this;
}

CsgRegularPolygon& CsgRegularPolygon::operator++(int)
{
    return ++(*this);
}
