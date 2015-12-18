#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include "vec2f.h"
#include "matrix33f.h"
#include <algorithm>

class BoundingBox
{
public:
    BoundingBox();
    BoundingBox(const BoundingBox &other);
    BoundingBox(float x1, float y1, float x2, float y2);
    BoundingBox(const std::pair<Vec2f, Vec2f> &xy1xy2);

    //Accesseurs//
    const Vec2f &XY1() const;
    const float &X1() const;
    const float &Y1() const;

    const Vec2f &XY2() const;
    const float &X2() const;
    const float &Y2() const;

    //Setteurs//
    void setXY1(const Vec2f &XY);
    void setX1(float x);
    void setY1(float y);

    void setXY2(const Vec2f &XY);
    void setX2(float x);
    void setY2(float y);

    //Opérateurs//

    BoundingBox operator+(const BoundingBox &other) const;
    BoundingBox operator-(const BoundingBox &other) const;
    BoundingBox operator^(const BoundingBox &other) const;

    //Opérations//

    bool collides(const BoundingBox &other) const;
    //std::pair<Vec3f, Vec3f> transform(const Matrix33f &trMatrix) const;

    void rotate(float rad);
    void translate(float tx, float ty);
    void scale(float vx, float vy);

private:

    std::pair<Vec2f, Vec2f> m_xy1xy2;
};

#endif // BOUNDINGBOX_H
