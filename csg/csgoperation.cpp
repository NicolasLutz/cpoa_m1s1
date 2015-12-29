#include "csgoperation.h"

CsgOperation::CsgOperation() :
    CsgNode(), m_type(CSG_NO_OPERATION), m_left(NULL), m_right(NULL)
{}

CsgOperation::CsgOperation(CsgOpType_t type, const std::string &label, CsgNode *left, CsgNode *right) :
    CsgNode(label), m_type(type), m_left(left), m_right(right)
{}

CsgOperation::CsgOperation(const CsgOperation &other) :
    CsgNode(other), m_type(other.Type()), m_left(other.Left()), m_right(other.Right())
{}

//----------------------------------------------------------------------------

CsgOperation::~CsgOperation()
{}

//----------------------------------------------------------------------------
//Accesseurs//

CsgOpType_t CsgOperation::Type() const
{
    return m_type;
}

CsgNode *CsgOperation::Left() const
{
    return m_left;
}

CsgNode *CsgOperation::Right() const
{
    return m_right;
}

//----------------------------------------------------------------------------
//Setters//

void CsgOperation::setType(CsgOpType_t type)
{
    m_type=type;
}

void CsgOperation::setLeft(CsgNode *left)
{
    m_left=left;
    left->setParent(this);
}

void CsgOperation::setRight(CsgNode *right)
{
    m_right=right;
    right->setParent(this);
}

//-----------------------------------------------------------------------------
//Opérations//

bool CsgOperation::intersects(const Vec2f &vertice) const
{
    bool itDoes=false;
    if(intersectsBBox(vertice))
    {
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
    return itDoes;
}

bool CsgOperation::intersectsBBox(const Vec2f &vertice) const
{
    return true;
}
