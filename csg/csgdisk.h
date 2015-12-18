#ifndef CSGDISK_H
#define CSGDISK_H

#include "csgprimitive.h"

class CsgDisk : public CsgPrimitive
{
public:
    CsgDisk();
    CsgDisk(const CsgDisk &other);
    CsgDisk(const Vec2f &origin);
    virtual ~CsgDisk();

    //Accesseurs//
    const float &Rx() const;
    const float &Ry() const;

    //Opérations//
    bool intersects(const Vec2f &vertice) const;
    void T_apply();
    void T_reset();

private:
    float m_rx;
    float m_ry;
};

#endif // CSGDISK_H
