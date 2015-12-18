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

void CsgOperation::T_apply()
{
    Left()->T_apply();
    Right()->T_apply();
}

void CsgOperation::T_reset()
{
    Left()->T_reset();
    Right()->T_reset();
}

//-----------------------------------------------------------------------------

void CsgOperation::T_rotate(float rad)
{
    Left()->T_rotate(rad);
    Right()->T_rotate(rad);
}

//-----------------------------------------------------------------------------

void CsgOperation::T_translate(float tx, float ty)
{
    Left()->T_translate(tx, ty);
    Right()->T_translate(tx, ty);
}

//-----------------------------------------------------------------------------

void CsgOperation::T_scale(float vx, float vy)
{
    Left()->T_scale(vx, vy);
    Right()->T_scale(vx, vy);
}

//Opérations//

bool CsgOperation::intersects(const Vec2f &vertice) const
{
    bool itDoes=false;
    switch(this->Type())
    {
        case CSG_UNION:
            itDoes=Left()->intersects(vertice) || Right()->intersects(vertice);
            break;
        case CSG_INTERSECTION:
            itDoes=Left()->intersects(vertice) && Right()->intersects(vertice);
            break;
        case CSG_DIF:
            itDoes=Left()->intersects(vertice) && !Right()->intersects(vertice);
            break;
        default:
            itDoes=false;
            break;
    }
}

