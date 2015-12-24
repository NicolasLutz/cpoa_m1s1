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
    return (*m_nodes.find(id)).second;
}
