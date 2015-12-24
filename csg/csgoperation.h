#ifndef CSGOPERATION_H
#define CSGOPERATION_H

#include "csgnode.h"

typedef enum {CSG_NO_OPERATION, CSG_UNION, CSG_INTERSECTION, CSG_DIF} CsgOpType_t;

class CsgOperation : public CsgNode
{
public:
    CsgOperation();
    CsgOperation(const CsgOperation &other);
    CsgOperation(CsgOpType_t type, const std::string &label, CsgNode *left=NULL, CsgNode *right=NULL);
    virtual ~CsgOperation();

    //Accesseurs//
    CsgOpType_t Type() const;
    CsgNode *Left() const;
    CsgNode *Right() const;

    //Setters//
    void setType(CsgOpType_t type);
    void setLeft(CsgNode *left);
    void setRight(CsgNode *right);

    //Transformations//
    bool intersects(const Vec2f &vertice) const;

private:
     CsgOpType_t    m_type;
     CsgNode        *m_left;
     CsgNode        *m_right;
};

#endif // CSGOPERATION_H
