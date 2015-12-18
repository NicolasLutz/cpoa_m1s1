#include "csgdisk.h"

CsgDisk::CsgDisk() : CsgPrimitive(), m_rx(1), m_ry(1)
{}

//----------------------------------------------------------------------------

CsgDisk::CsgDisk(const CsgDisk &other) : CsgPrimitive(other), m_rx(other.Rx()), m_ry(other.Ry())
{}

//----------------------------------------------------------------------------

CsgDisk::~CsgDisk()
{}

//----------------------------------------------------------------------------
//Accesseurs//

const float& CsgDisk::Rx() const
{
    return m_rx;
}

const float& CsgDisk::Ry() const
{
    return m_ry;
}

//----------------------------------------------------------------------------
//Opérations//

bool CsgDisk::intersects(const Vec2f &vertice) const
{
    if(Rx()==Ry())
    {
        return Rx()>=vertice.distance(Origin());
    }
    return (std::pow(vertice.X()-Origin().X(), 2)/std::pow(Rx(), 2))
            + (std::pow(vertice.Y()-Origin().Y(), 2)/std::pow(Ry(), 2)) <= 1.0f;
}

void CsgDisk::T_apply()
{
    CsgPrimitive::T_apply();
}

void CsgDisk::T_reset()
{
    CsgPrimitive::T_reset();
    m_rx=1.0f;
    m_ry=1.0f;
}
