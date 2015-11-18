#ifndef CSGOPERATION_H
#define CSGOPERATION_H

#include "csgnode.h"

typedef enum {CSG_UNION, CSG_INTERSECTION, CSG_SYM_DIF} csgOpType_t;

class CsgOperation : public CsgNode
{
public:
    CsgOperation();
    CsgOperation(const CsgOperation &other);
    virtual ~CsgOperation();

    //Accesseurs//
    csgOpType_t Type();

private:
     csgOpType_t m_type;
};

#endif // CSGOPERATION_H
