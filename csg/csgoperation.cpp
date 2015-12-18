#include "csgoperation.h"

CsgOperation::CsgOperation() :
    CsgNode(), m_type(CSG_NO_OPERATION)
{}

CsgOperation::CsgOperation(const std::string &label, CsgOpType_t type, CsgNode *left, CsgNode *right) :
    CsgNode(label, left, right), m_type(type)
{}

//----------------------------------------------------------------------------

CsgOperation::CsgOperation(const CsgOperation &other) :
    CsgNode(other), m_type(other.Type())
{}

//----------------------------------------------------------------------------

CsgOperation::~CsgOperation()
{}

//----------------------------------------------------------------------------

CsgOpType_t CsgOperation::Type() const
{
    return m_type;
}

//-----------------------------------------------------------------------------
//Transformations//

void CsgOperation::T_reset()
{
    if(Left()!=NULL)
        Left()->T_reset();
    if(Right()!=NULL)
        Right()->T_reset();
}

//-----------------------------------------------------------------------------

void CsgOperation::T_rotate(float rad)
{
    if(Left()!=NULL)
        Left()->T_rotate(rad);
    if(Right()!=NULL)
        Right()->T_rotate(rad);
}

//-----------------------------------------------------------------------------

void CsgOperation::T_translate(float tx, float ty)
{
    if(Left()!=NULL)
        Left()->T_translate(tx, ty);
    if(Right()!=NULL)
        Right()->T_translate(tx, ty);
}

//-----------------------------------------------------------------------------

void CsgOperation::T_scale(float vx, float vy)
{
    if(Left()!=NULL)
        Left()->T_scale(vx, vy);
    if(Right()!=NULL)
        Right()->T_scale(vx, vy);
}
