#include "csgprimitive.h"

CsgPrimitive::CsgPrimitive():
    CsgNode(), m_origin(0,0)
{}

//----------------------------------------------------------------------------

CsgPrimitive::CsgPrimitive(Point origin):
    CsgNode(), m_origin(origin)
{}

//----------------------------------------------------------------------------

CsgPrimitive::CsgPrimitive(const CsgPrimitive &other):
    CsgNode(other), m_origin(other.getOrigin())
{}

//----------------------------------------------------------------------------

CsgPrimitive::~CsgPrimitive()
{

}

//----------------------------------------------------------------------------
//Accesseurs//

Point& CsgPrimitive::getOrigin()
{
    return m_origin;
}

const Point& CsgPrimitive::getOrigin() const
{
    return m_origin;
}
