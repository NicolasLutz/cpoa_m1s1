#ifndef FUNC__H
#define FUNC__H

#include "particle.h"

class Func_AbsoluteDateOrder
{
public:
    Func_AbsoluteDateOrder();
    bool operator()(const Particle* object, const Particle* other) const;
};

#endif // FUNC__H
