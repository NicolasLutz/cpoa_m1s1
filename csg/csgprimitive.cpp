#include "csgprimitive.h"

const Vec2f CsgPrimitive::sc_origin(0,0);

CsgPrimitive::CsgPrimitive():
    CsgNode(), m_T_matrix(), m_T_inverted(), m_T_saved()
{
}

//----------------------------------------------------------------------------

CsgPrimitive::CsgPrimitive(const CsgPrimitive &other):
    CsgNode(other), m_T_matrix(other.T_Matrix()), m_T_inverted(other.T_Inverted()), m_T_saved(other.T_Saved())
{}

//----------------------------------------------------------------------------

CsgPrimitive::~CsgPrimitive()
{}

//----------------------------------------------------------------------------
//Accesseurs//

const Vec2f& CsgPrimitive::Origin() const
{
    return sc_origin;
}

//----------------------------------------------------------------------------
//Transformations//

void CsgPrimitive::T_applyTransfo(float tx, float ty, float rad, float vx, float vy)
{
    m_T_matrix.setId();
    m_T_matrix.addRotation(rad);
    m_T_matrix.addScaling(vx, vy);
    m_T_matrix.addTranslation(tx, ty);
    m_T_inverted=m_T_matrix.invert();
    updateBB();
}

const Matrix33f& CsgPrimitive::T_Matrix() const
{
    return m_T_matrix;
}

const Matrix33f& CsgPrimitive::T_Inverted() const
{
    return m_T_inverted;
}

const Matrix33f& CsgPrimitive::T_Saved() const
{
    return m_T_saved;
}

//----------------------------------------------------------------------------

void CsgPrimitive::T_save()
{
    m_T_saved=m_T_matrix;
}

void CsgPrimitive::T_reset()
{
    m_T_matrix = m_T_saved;
    m_T_inverted = m_T_saved.invert();
    updateBB();
}

void CsgPrimitive::T_nullify()
{
    m_T_matrix.setId();
    m_T_inverted.setId();
    m_T_saved.setId();
    updateBB();
}

//----------------------------------------------------------------------------

void CsgPrimitive::T_set(const Matrix33f &transfo)
{
    m_T_matrix=transfo;
    m_T_inverted=transfo.invert();
    updateBB();
}

//----------------------------------------------------------------------------

bool CsgPrimitive::intersectsBBox(const Vec2f &vertice) const
{
    return vertice.X()>=m_BB.X1() && vertice.X()<=m_BB.X2() && vertice.Y()>=m_BB.Y1() && vertice.Y()<=m_BB.Y2();
}

void CsgPrimitive::updateBB()
{
    m_BB.applyTransfo(m_T_matrix, _baseBB1(), _baseBB2());
    if(m_parent!=NULL)
        m_parent->updateBB();
}

const Vec2f& CsgPrimitive::_baseBB1() const
{
    return Origin();
}

const Vec2f& CsgPrimitive::_baseBB2() const
{
    return Origin();
}
