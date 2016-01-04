#ifndef CSGTREE_H
#define CSGTREE_H

#include "csgprimitive.h"
#include "csgoperation.h"
#include "_func.h"
#include <set>
#include <map>

class CsgTree
{
public:
    CsgTree();
    CsgTree(const CsgTree &other);
    virtual ~CsgTree();

    //Accesseurs

    std::set<CsgNode *, Func_CSGT_Compare>& Roots();
    std::set<CsgNode *, Func_CSGT_Compare>& Leafs();

    //Opérations

    CsgNode* add(CsgNode *node);
    CsgNode* join(CsgOperation *operation, CsgNode *node, CsgNode *otherNode);
    CsgNode *fromId(int id);
    void clear();
    void removeId(int id);

    //Itérateurs//
    typedef std::map<int, CsgNode *>::iterator iterator;
    typedef std::map<int, CsgNode *>::const_iterator const_iterator;

    iterator begin();
    iterator end();

    const_iterator begin() const;
    const_iterator end() const;

private:
    std::set<CsgNode *, Func_CSGT_Compare>   m_roots;
    std::set<CsgNode *, Func_CSGT_Compare>   m_leafs;
    std::map<int, CsgNode *>   m_nodes;
};

#endif // CSGTREE_H
