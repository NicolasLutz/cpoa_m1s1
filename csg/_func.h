#ifndef _FUNC_H
#define _FUNC_H

#include <csgnode.h>
#include "vector.hpp"

class Func_CSGT_Compare
{
public:
    Func_CSGT_Compare();
    bool operator()(CsgNode *object, CsgNode *other) const;

private:
};

#endif // _FUNC_H
