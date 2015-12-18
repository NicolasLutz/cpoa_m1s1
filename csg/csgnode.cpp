#include "csgnode.h"

unsigned int CsgNode::s_count=0;

CsgNode::CsgNode() :
    m_id(s_count++), m_label(""), m_left(NULL), m_right(NULL)
{}

CsgNode::CsgNode(const std::string &label, CsgNode *left, CsgNode *right) :
    m_id(s_count++), m_label(label), m_left(left), m_right(right)
{}

//----------------------------------------------------------------------------

CsgNode::CsgNode(const CsgNode &other) :
    m_id(s_count++), m_label(other.Label()), m_left(other.Left()), m_right(other.Right())
{}

//----------------------------------------------------------------------------

CsgNode::~CsgNode()
{}

//----------------------------------------------------------------------------
//Accesseurs//

const std::string& CsgNode::Label() const
{
    return m_label;
}

//----------------------------------------------------------------------------

const unsigned int &CsgNode::Id() const
{
    return m_id;
}

//----------------------------------------------------------------------------

CsgNode *CsgNode::Left() const
{
    return m_left;
}

//----------------------------------------------------------------------------

CsgNode *CsgNode::Right() const
{
    return m_right;
}

//----------------------------------------------------------------------------
//Setteurs//

void CsgNode::setLeft(CsgNode *left)
{
    m_left=left;
}

//----------------------------------------------------------------------------

void CsgNode::setRight(CsgNode *right)
{
    m_right=right;
}

//----------------------------------------------------------------------------

void CsgNode::setLabel(const std::string &label)
{
    m_label=label;
}

//----------------------------------------------------------------------------

//TODO : is parent useful ?
////----------------------------------------------------------------------------

//CsgNode *CsgNode::Parent() const
//{
//    return m_parent;
//}

////----------------------------------------------------------------------------

//void CsgNode::setParent(CsgNode *parent)
//{
//    m_parent=parent;
//}
