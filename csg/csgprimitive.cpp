#include "csgprimitive.h"

CsgPrimitive::CsgPrimitive():
    CsgNode(), m_origin(0,0)
{}

//----------------------------------------------------------------------------

CsgPrimitive::CsgPrimitive(Vec2f origin):
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

Vec2f& CsgPrimitive::getOrigin()
{
    return m_origin;
}

const Vec2f& CsgPrimitive::getOrigin() const
{
    return m_origin;
}
