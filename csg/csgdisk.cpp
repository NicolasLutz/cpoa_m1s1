#include "csgdisk.h"

CsgDisk::CsgDisk() : CsgPrimitive(), m_radius(1)
{}

//----------------------------------------------------------------------------

CsgDisk::CsgDisk(const CsgDisk &other) : CsgPrimitive(other), m_radius(other.Radius())
{}

//----------------------------------------------------------------------------

CsgDisk::~CsgDisk()
{}

//----------------------------------------------------------------------------
//Accesseurs//

const float& CsgDisk::Radius() const
{
    return m_radius;
}

//----------------------------------------------------------------------------
//Opérations//

bool CsgDisk::isInside(const Vec2f &vertice) const
{
    return m_radius>=Origin().distance(vertice);
}
