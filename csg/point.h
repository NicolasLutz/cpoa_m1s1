#ifndef POINT_H
#define POINT_H

#include <utility>

class Point : std::pair<float,float>
{
public:
    Point();
    Point(float x, float y);
    Point(const Point &other);
    float& X();
    const float& X() const;
    float& Y();
    const float& Y() const;
};

#endif // POINT_H
