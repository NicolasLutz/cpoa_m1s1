#include "csgnode.h"

unsigned int CsgNode::s_count=0;

CsgNode::CsgNode() :
    m_id(s_count++), m_label(""), m_left(NULL), m_right(NULL)
{
    std::cout << "Creating node " << (!m_label.empty() ? m_label : std::string("<no name>")) << " of id " << m_id << std::endl;
}

//----------------------------------------------------------------------------

CsgNode::CsgNode(const CsgNode &other) :
    m_id(s_count++), m_label(other.Label()), m_left(other.Left()), m_right(other.Right())
{
    std::cout << "Creating node " << (!m_label.empty() ? m_label : std::string("<no name>")) << " of id " << m_id << std::endl;
}

//----------------------------------------------------------------------------

CsgNode::~CsgNode()
{
    std::cout << "Destroying node " << (!m_label.empty() ? m_label : std::string("<no name>")) << " of id " << m_id << std::endl;
}

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
