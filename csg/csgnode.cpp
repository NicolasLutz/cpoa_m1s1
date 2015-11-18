#include "csgnode.h"

CsgNode::CsgNode() :
    m_id(0), m_label(""), m_parent(0)
{
    std::cout << "Creating node " << (!m_label.empty() ? m_label : std::string("<no name>")) << " of id " << m_id << std::endl;
}

//----------------------------------------------------------------------------

CsgNode::CsgNode(const CsgNode &other) :
    m_id(other.id()), m_label(other.label()), m_parent(other.parent())
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

std::string CsgNode::label() const
{
    return m_label;
}

//----------------------------------------------------------------------------

int CsgNode::id() const
{
    return m_id;
}

//----------------------------------------------------------------------------

CsgNode *CsgNode::parent() const
{
    return m_parent;
}

//----------------------------------------------------------------------------

void CsgNode::setParent(CsgNode *parent)
{
    m_parent=parent;
}
