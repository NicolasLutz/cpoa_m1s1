#ifndef VEC2F_H
#define VEC2F_H

#include "vector.hpp"

class Vec2f : public Vector<2u, float>
{
public:

    //Constructeurs
    Vec2f();

    Vec2f(float x, float y=0);

    Vec2f(const Vec2f& other);

    //Opérateurs

    float operator*(const Vec2f& other) const;

    Vec2f operator+(const Vec2f& other) const; //corrige un bug étrange ???

    const Vec2f& operator*=(float fValue);
    const Vec2f& operator*=(unsigned int uiValue);
    const Vec2f& operator*=(int iValue);
    const Vec2f& operator*=(double lfValue);
    const Vec2f& operator*=(long int liValue);

    Vec2f operator*(float fValue) const;
    Vec2f operator*(unsigned int uiValue) const;
    Vec2f operator*(int iValue) const;
    Vec2f operator*(double lfValue) const;
    Vec2f operator*(long int liValue) const;

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
