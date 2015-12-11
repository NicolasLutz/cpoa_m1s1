#include "csgtree.h"

CsgTree::CsgTree() : m_roots(), m_leafs()
{

}

//----------------------------------------------------------------------------

CsgTree::CsgTree(const CsgTree &other) : m_roots(), m_leafs() //TODO
{}

//----------------------------------------------------------------------------

CsgTree::~CsgTree()
{

}

//----------------------------------------------------------------------------

void CsgTree::add(CsgPrimitive *primitive)
{
    m_roots.insert(primitive);
    m_leafs.insert(primitive);//primitive is also a leaf
}

void CsgTree::join(CsgNode *node, CsgNode *otherNode, CsgOperation *operation)
{
    m_roots.erase(node);
    m_roots.erase(otherNode);
    m_roots.insert(operation);
    operation->setLeft(node);
    operation->setRight(otherNode);
}
