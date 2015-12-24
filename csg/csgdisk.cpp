#include "csgdisk.h"

CsgDisk::CsgDisk() : CsgPrimitive()
{}

//----------------------------------------------------------------------------

CsgDisk::CsgDisk(const CsgDisk &other) : CsgPrimitive(other)
{}

//----------------------------------------------------------------------------

CsgDisk::~CsgDisk()
{}

//----------------------------------------------------------------------------
//Opérations//

bool CsgDisk::intersects(const Vec2f &vertice) const
{
    Vec2f transformedVertice = T_Inverted() * vertice;
    return transformedVertice.distance(Origin()) <= 1.0f;
}
