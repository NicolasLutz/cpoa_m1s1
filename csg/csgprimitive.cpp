#include "csgprimitive.h"

CsgPrimitive::CsgPrimitive():
    CsgNode(), m_origin(0,0), m_T_matrix()
{}

//----------------------------------------------------------------------------

CsgPrimitive::CsgPrimitive(const CsgPrimitive &other):
    CsgNode(other), m_origin(other.Origin()), m_T_matrix(other.T_Matrix())
{}

//----------------------------------------------------------------------------

CsgPrimitive::~CsgPrimitive()
{}

//----------------------------------------------------------------------------
//Accesseurs//

Vec2f& CsgPrimitive::Origin()
{
    return m_origin;
}

const Vec2f& CsgPrimitive::Origin() const
{
    return m_origin;
}

const Matrix33f& CsgPrimitive::T_Matrix() const
{
    return m_T_matrix;
}

void CsgPrimitive::T_reset()
{
    m_T_matrix.setId();
}

void CsgPrimitive::T_rotate(float rad)
{
    m_T_matrix.addRotation(rad);
}

void CsgPrimitive::T_translate(float tx, float ty)
{
    m_T_matrix.addTranslation(tx,ty);
}

void CsgPrimitive::T_scale(float vx, float vy)
{
    m_T_matrix.addScaling(vx, vy);
}
