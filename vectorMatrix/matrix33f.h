#ifndef MATRIX33F_H
#define MATRIX33F_H

#include "vec3f.h"
#include <cmath>

class Matrix33f : public Array<3, Vec3f>
{
public:

    //Constructeurs

    Matrix33f();

    Matrix33f(const Matrix33f &other);

    //Opérateurs
    //Accès à l'élément de la ième ligne et jème colonne : Matrix33f[i][j] ou Matrix33f[i].<X(),Y(),Z()>
    //Accès à la ième ligne : Matrix33f[i]
    //Commence à 0

    Vec3f operator*(const Vec3f& vector) const;

    //Opérations

    void setInvert();

    void setId();

    void setTranslation(float tx, float ty);
    void setRotation(float rad);
    void setScaling(float vx, float vy);

    void addTranslation(float tx, float ty);
    void addRotation(float rad);
    void addScaling(float vx, float vy);

    void apply(Vec2f &vector) const;

};

#endif // MATRIX33F_H
