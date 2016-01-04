#include "csgoperation.h"

CsgOperation::CsgOperation() :
    CsgNode(), m_type(CSG_NO_OPERATION), m_left(NULL), m_right(NULL)
{}

CsgOperation::CsgOperation(CsgOpType_t type, const std::string &label, CsgNode *left, CsgNode *right) :
    CsgNode(label), m_type(type), m_left(left), m_right(right)
{
    updateBB();
}

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
    updateBB();
}

void CsgOperation::setLeft(CsgNode *left)
{
    if(m_left!=NULL)
        m_left->setParent(NULL);
    m_left=left;
    if(left!=NULL)
        left->setParent(this);
    updateBB();
}

void CsgOperation::setRight(CsgNode *right)
{
    if(m_right!=NULL)
        m_right->setParent(NULL);
    m_right=right;
    if(right!=NULL)
        right->setParent(this);
    updateBB();
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

void CsgOperation::updateBB()
{
    if(m_left==NULL || m_right==NULL)
        return;
    switch(m_type)
    {
        case CSG_UNION:
            m_BB= m_left->BBox() + m_right->BBox();
            break;
        case CSG_INTERSECTION:
            m_BB= m_left->BBox() ^ m_right->BBox();
            break;
        case CSG_DIF:
            m_BB= m_left->BBox() - m_right->BBox();
            break;
        default:
            break;
    }
    if(m_parent!=NULL)
        m_parent->updateBB();
    return;
}

CsgNode* CsgOperation::clone() const
{
    return new CsgOperation(*this);
}

void CsgOperation::swap()
{
    CsgNode *l=Left();
    setLeft(Right());
    setRight(l);
    updateBB();
}

//Autres//

std::ostream& CsgOperation::print(std::ostream &stream) const
{
    stream << 'O' _spc_output_
              /*'\"' << object.Label() << '\"' _spc_output_*/
              (int)Type() _spc_output_
              Left()->Id() _spc_output_
              Right()->Id() << std::endl;
    return stream;
}

std::istream& CsgOperation::scan(std::istream &stream)
{
    int op, l, r;
    stream >> op >> l >> r;
    setType((CsgOpType_t)op);
    setLeft((CsgNode *)l);
    setRight((CsgNode *)r);
    return stream;
}
