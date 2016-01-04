#include "csgnode.h"

unsigned int CsgNode::s_count=0;

CsgNode::CsgNode() :
    m_id(s_count++), m_label(""), m_parent(NULL), m_BB()
{}

CsgNode::CsgNode(const std::string &label) :
    m_id(s_count++), m_label(label), m_parent(NULL), m_BB()
{}

//----------------------------------------------------------------------------

CsgNode::CsgNode(const CsgNode &other) :
    m_id(s_count++), m_label(other.Label()), m_parent(NULL), m_BB(other.BBox())
{}

//----------------------------------------------------------------------------

CsgNode::~CsgNode()
{}

//----------------------------------------------------------------------------
//Accesseurs//

const unsigned int& CsgNode::Id() const
{
    return m_id;
}

const std::string& CsgNode::Label() const
{
    return m_label;
}

CsgNode* CsgNode::Parent() const
{
    return m_parent;
}

const BoundingBox& CsgNode::BBox() const
{
    return m_BB;
}

//----------------------------------------------------------------------------
//Setteurs//

void CsgNode::setParent(CsgNode *parent)
{
    m_parent=parent;
}

void CsgNode::setLabel(const std::string &label)
{
    m_label=label;
}

//----------------------------------------------------------------------------
//Statique//

void CsgNode::resetCounter()
{
    s_count=0;
}

unsigned int CsgNode::Counter()
{
    return s_count;
}

//----------------------------------------------------------------------------
//Autre//

std::ostream& operator<< (std::ostream &stream, const CsgNode &object)
{
    return object.print(stream);
}

std::istream& operator>> (std::istream &stream, CsgNode &object)
{
    return object.scan(stream);
}
