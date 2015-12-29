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

    //Opérations//
    bool intersects(const Vec2f &vertice) const;
    bool intersectsBBox(const Vec2f &vertice) const;
};

#endif // CSGDISK_H
