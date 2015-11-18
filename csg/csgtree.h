#ifndef CSGTREE_H
#define CSGTREE_H

#include "csgnode.h"
#include <set>

class CsgTree
{
public:
    CsgTree();
    CsgTree(const CsgTree &other);
    //explicit CsgTree(CsgTree * const left, CsgTree * const right);
    virtual ~CsgTree();

    //Accesseurs

private:
    std::set<CsgNode>   m_roots;
};

#endif // CSGTREE_H
