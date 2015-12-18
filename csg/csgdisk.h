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
    const float &Radius() const;

    //Opérations//
    bool isInside(const Vec2f &vertice) const;


private:
    float m_radius;
};

#endif // CSGDISK_H
