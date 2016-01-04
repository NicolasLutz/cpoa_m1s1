#include "_func_particle.h"

Func_AbsoluteDateOrder::Func_AbsoluteDateOrder()
{}

bool Func_AbsoluteDateOrder::operator()(const Particle* object, const Particle* other) const
{
    return object->getPriority() >= other->getPriority();
}
