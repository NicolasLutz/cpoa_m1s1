#ifndef VEC3F_H
#define VEC3F_H

#include "vec2f.h"

class Vec3f : public Vector<3u, float>
{
public:

    //Constructeurs
    Vec3f();

    Vec3f(float x, float y, float z);

    Vec3f(const Vec3f &other);

    Vec3f(const Vec2f &vector2, float z);

    //Opérateurs

    float operator*(const Vec3f& other) const;

    Vec3f operator^(const Vec3f& other) const;

    const Vec3f& operator*=(float fValue);
    const Vec3f& operator*=(unsigned int uiValue);
    const Vec3f& operator*=(int iValue);
    const Vec3f& operator*=(double lfValue);
    const Vec3f& operator*=(long int liValue);

    Vec3f operator*(float fValue) const;
    Vec3f operator*(unsigned int uiValue) const;
    Vec3f operator*(int iValue) const;
    Vec3f operator*(double lfValue) const;
    Vec3f operator*(long int liValue) const;

    //Accesseurs

    const float &X() const;
    const float &Y() const;
    const float &Z() const;
    Vec2f XY() const;

    //Setters

    void setX(float x);
    void setY(float y);
    void setZ(float z);
};

//------------------------------------------------
//------------------------------------------------

Vec3f operator^(const Vec2f& v_this, const Vec2f& other);

#endif // VEC3F_H
