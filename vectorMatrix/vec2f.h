#ifndef VEC2F_H
#define VEC2F_H

#include "vector.hpp"

class Vec2f : public Vector<2>
{
public:

    //Constructeurs
    Vec2f();

    Vec2f(float x, float y);

    Vec2f(const Vec2f& other);

    //Opérateurs

    float operator*(const Vec2f& other) const;

    //Accesseurs

    const float &X() const;
    const float &Y() const;

    //Setters

    void setX(float x);
    void setY(float y);
};

//------------------------------------------------
//------------------------------------------------

#endif // VEC2F_H
