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

    //Transformations//
    virtual void T_applyTransfo(float tx, float ty,
                                float rad,
                                float vx, float vy); ///< sets transfo

    //Opérations//
    bool intersects(const Vec2f &vertice) const;
    CsgNode *clone() const;

    //Autre//
    std::ostream& print(std::ostream &stream) const;
    std::istream& scan(std::istream &stream);

private:
    const Vec2f& _baseBB1() const;
    const Vec2f& _baseBB2() const;

    static const Vec2f sc_baseBB1;
    static const Vec2f sc_baseBB2;
};

#endif // CSGDISK_H
