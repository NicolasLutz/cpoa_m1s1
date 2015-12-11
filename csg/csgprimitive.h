#ifndef CSGPRIMITIVE_H
#define CSGPRIMITIVE_H

#include "csgnode.h"
#include "vec2f.h"

class CsgPrimitive : public CsgNode
{
public:
    //Constructeurs//
    CsgPrimitive();
    CsgPrimitive(Vec2f origin);
    CsgPrimitive(const CsgPrimitive &other);
    virtual ~CsgPrimitive();

    //Accesseurs//
    Vec2f& getOrigin();
    const Vec2f& getOrigin() const;

private:
    Vec2f m_origin;
};

#endif // CSGPRIMITIVE_H
