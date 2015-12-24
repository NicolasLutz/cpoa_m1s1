#include "csgnode.h"

unsigned int CsgNode::s_count=0;

CsgNode::CsgNode() :
    m_id(s_count++), m_label(""), m_parent(NULL)
{}

CsgNode::CsgNode(const std::string &label) :
    m_id(s_count++), m_label(label), m_parent(NULL)
{}

//----------------------------------------------------------------------------

CsgNode::CsgNode(const CsgNode &other) :
    m_id(s_count++), m_label(other.Label()), m_parent(NULL)
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

CsgNode *CsgNode::Parent() const
{
    return m_parent;
}

//----------------------------------------------------------------------------
//Setteurs//

void CsgNode::setParent(CsgNode *parent)
{
    m_parent=parent;
}

//----------------------------------------------------------------------------

void CsgNode::setLabel(const std::string &label)
{
    m_label=label;
}
