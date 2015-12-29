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

    void add(CsgPrimitive *primitive);
    void join(CsgOperation *operation, CsgNode *node, CsgNode *otherNode);
    CsgNode *fromId(int id);

private:
    std::set<CsgNode *, Func_CSGT_Compare>   m_roots;
    std::set<CsgNode *, Func_CSGT_Compare>   m_leafs;
    std::map<int, CsgNode *>   m_nodes;
};

#endif // CSGTREE_H
