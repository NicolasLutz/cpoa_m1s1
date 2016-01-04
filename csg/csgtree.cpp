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

//----------------------------------------------------------------------------

CsgNode* CsgTree::add(CsgNode *node)
{
    m_roots.insert(node);
    m_leafs.insert(node);//primitive is also a leaf
    m_nodes.insert(std::pair<int, CsgNode *>(node->Id(), node));//direct access
    return node;
}

CsgNode* CsgTree::join(CsgOperation *operation, CsgNode *node, CsgNode *otherNode)
{
    m_nodes.insert(std::pair<int, CsgNode *>(operation->Id(), operation));
    m_roots.erase(node);
    m_roots.erase(otherNode);
    m_roots.insert(operation);
    operation->setLeft(node);
    operation->setRight(otherNode);
    return operation;
}

CsgNode *CsgTree::fromId(int id)
{
    std::map<int, CsgNode *>::iterator it=m_nodes.find(id);
    return it!=m_nodes.end() ? (*it).second : NULL;
}

void CsgTree::removeId(int id)
{
    CsgNode *foundNode;
    std::map<int, CsgNode *>::iterator it=m_nodes.find(id);
    if(it!=m_nodes.end())
    {
        foundNode=(*it).second;
        m_nodes.erase(it);
        std::set<CsgNode*>::iterator other_it=m_roots.find(foundNode);
        if(other_it!=m_roots.end())
            m_roots.erase(other_it);
        other_it=m_leafs.find(foundNode);
        if(other_it!=m_leafs.end())
            m_leafs.erase(other_it);
        delete foundNode;
    }
}

void CsgTree::clear()
{
    m_roots.erase(m_roots.begin(), m_roots.end());
    m_leafs.erase(m_leafs.begin(), m_leafs.end());
    for(std::map<int, CsgNode *>::iterator it=m_nodes.begin(); it!=m_nodes.end(); ++it)
    {
        delete (*it).second;
    }
    m_nodes.erase(m_nodes.begin(), m_nodes.end());
    CsgNode::resetCounter();
}

//----------------------------------------------------------------------------
//Itérateurs//

CsgTree::iterator CsgTree::begin()
{
    return m_nodes.begin();
}

CsgTree::iterator CsgTree::end()
{
    return m_nodes.end();
}

CsgTree::const_iterator CsgTree::begin() const
{
    return m_nodes.begin();
}

CsgTree::const_iterator CsgTree::end() const
{
    return m_nodes.end();
}
