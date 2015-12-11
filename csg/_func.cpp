#include "_func.h"

Func_CSGT_Compare::Func_CSGT_Compare()
{
}

bool Func_CSGT_Compare::operator()(CsgNode *object, CsgNode *other) const
{
    if(object==NULL || other==NULL)
    {
        return false;
    }
    return object->Id() < other->Id();
}

//----------------------------------------------------------------------------
