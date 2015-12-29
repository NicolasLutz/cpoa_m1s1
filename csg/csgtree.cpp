#include "csgtree.h"

CsgTree::CsgTree() : m_roots(), m_leafs(), m_nodes()
{}

//----------------------------------------------------------------------------

CsgTree::CsgTree(const CsgTree &other) : m_roots(), m_leafs(), m_nodes() //TODO
{}

//----------------------------------------------------------------------------

CsgTree::~CsgTree()
{}

//----------------------------------------------------------------------------

std::set<CsgNode *, Func_CSGT_Compare>& CsgTree::Roots()
{
    return m_roots;
}

std::set<CsgNode *, Func_CSGT_Compare>& CsgTree::Leafs()
{
    return m_leafs;
}

void CsgTree::add(CsgPrimitive *primitive)
{
    m_roots.insert(primitive);
    m_leafs.insert(primitive);//primitive is also a leaf
    m_nodes.insert(std::pair<int, CsgNode *>(primitive->Id(), primitive));//direct access
}

void CsgTree::join(CsgOperation *operation, CsgNode *node, CsgNode *otherNode)
{
    m_nodes.insert(std::pair<int, CsgNode *>(operation->Id(), operation));
    m_roots.erase(node);
    m_roots.erase(otherNode);
    m_roots.insert(operation);
    operation->setLeft(node);
    operation->setRight(otherNode);
}

CsgNode *CsgTree::fromId(int id)
{
    std::map<int, CsgNode *>::iterator it=m_nodes.find(id);
    return it!=m_nodes.end() ? (*it).second : NULL;
}
