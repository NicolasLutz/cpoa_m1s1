#ifndef CSGOPERATION_H
#define CSGOPERATION_H

#include "csgnode.h"

typedef enum {CSG_NO_OPERATION, CSG_UNION, CSG_INTERSECTION, CSG_DIF} CsgOpType_t;

class CsgOperation : public CsgNode
{
public:
    CsgOperation();
    CsgOperation(const std::string &label, CsgOpType_t type, CsgNode *left=NULL, CsgNode *right=NULL);
    CsgOperation(const CsgOperation &other);
    virtual ~CsgOperation();

    //Accesseurs//
    CsgOpType_t Type() const;

    //Transformations//
    void T_apply();
    void T_reset();
    void T_rotate(float rad);
    void T_translate(float tx, float ty);
    void T_scale(float vx, float vy);

    bool intersects(const Vec2f &vertice) const;

private:
     CsgOpType_t m_type;
};

#endif // CSGOPERATION_H
