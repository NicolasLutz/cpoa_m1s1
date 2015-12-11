#ifndef CSGTREE_H
#define CSGTREE_H

#include "csgprimitive.h"
#include "csgoperation.h"
#include "_func.h"
#include <set>

class CsgTree
{
public:
    CsgTree();
    CsgTree(const CsgTree &other);
    virtual ~CsgTree();

    //Accesseurs

    //Opérations

    void add(CsgPrimitive *primitive);
    void join(CsgNode *node, CsgNode *otherNode, CsgOperation *operation);

private:
    std::set<CsgNode *, Func_CSGT_Compare>   m_roots;
    std::set<CsgNode *, Func_CSGT_Compare>   m_leafs;
};

#endif // CSGTREE_H
