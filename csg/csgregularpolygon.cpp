#include "csgregularpolygon.h"

CsgRegularPolygon::CsgRegularPolygon() : CsgPrimitive(), m_vertices(3)
{}

//----------------------------------------------------------------------------

CsgRegularPolygon::CsgRegularPolygon(const CsgRegularPolygon &other) : CsgPrimitive(other), m_vertices(other.Vertices())
{}

//----------------------------------------------------------------------------

CsgRegularPolygon::CsgRegularPolygon(unsigned int nb_vertices) : CsgPrimitive(), m_vertices(nb_vertices)
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

//----------------------------------------------------------------------------
//Opérations//

bool CsgRegularPolygon::intersects(const Vec2f &vertice) const
{
    return false; //TODO
}

void CsgRegularPolygon::T_apply()
{
    CsgPrimitive::T_apply();
}

void CsgRegularPolygon::T_reset()
{
    CsgPrimitive::T_reset();
}
