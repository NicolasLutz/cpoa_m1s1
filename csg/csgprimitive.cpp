#include "csgprimitive.h"

const Vec2f CsgPrimitive::sc_origin(0,0);

CsgPrimitive::CsgPrimitive():
    CsgNode(), m_T_matrix(), m_T_inverted(), m_T_saved()
{}

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
}

void CsgPrimitive::T_nullify()
{
    m_T_matrix.setId();
    m_T_inverted.setId();
    m_T_saved.setId();
}

//----------------------------------------------------------------------------

void CsgPrimitive::T_set(const Matrix33f &transfo)
{
    m_T_matrix=transfo;
    m_T_inverted=transfo.invert();
}

//----------------------------------------------------------------------------
//Opérations//

