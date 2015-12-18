#ifndef CSGPRIMITIVE_H
#define CSGPRIMITIVE_H

#include "csgnode.h"
#include "matrix33f.h"

class CsgPrimitive : public CsgNode
{
public:
    //Constructeurs//
    CsgPrimitive();
    CsgPrimitive(const CsgPrimitive &other);
    CsgPrimitive(const Vec2f &origin);
    virtual ~CsgPrimitive();

    //Accesseurs//
    Vec2f&   Origin();
    const Vec2f& Origin() const;
    const Matrix33f& T_Matrix() const;

    //Opérations//
    virtual bool isInside(const Vec2f& other) const=0;

    //Transformations//
    void T_reset();
    void T_rotate(float rad);
    void T_translate(float tx, float ty);
    void T_scale(float vx, float vy);

private:
    Vec2f m_origin;
    Matrix33f m_T_matrix;
};

#endif // CSGPRIMITIVE_H
