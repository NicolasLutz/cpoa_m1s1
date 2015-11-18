#ifndef CSGDISK_H
#define CSGDISK_H

#include "csgprimitive.h"

class CsgDisk : public CsgPrimitive
{
public:
    CsgDisk();
    CsgDisk(const CsgDisk &other);
    virtual ~CsgDisk();

private:
    float m_radius;
};

#endif // CSGDISK_H
