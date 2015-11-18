#ifndef CSGPRIMITIVE_H
#define CSGPRIMITIVE_H

#include "csgnode.h"
#include "point.h"

class CsgPrimitive : public CsgNode
{
public:
    //Constructeurs//
    CsgPrimitive();
    CsgPrimitive(Point origin);
    CsgPrimitive(const CsgPrimitive &other);
    virtual ~CsgPrimitive();

    //Accesseurs//
    Point& getOrigin();
    const Point& getOrigin() const;

private:
    Point m_origin;
};

#endif // CSGPRIMITIVE_H
