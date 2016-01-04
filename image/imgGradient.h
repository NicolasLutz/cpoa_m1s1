#ifndef IMGGRADIENT_H
#define IMGGRADIENT_H

#include "image2grey.h"
#include "vec2f.h"

typedef enum {GRAD_33, GRAD_55} Sobel_t;

class GradientSobel
{
public:
    GradientSobel();

    Image2<Vec2f> gradient33(const Image2Grey& img_in) const;
    Image2<Vec2f> gradient55(const Image2Grey& img_in) const;

    Image2<Vec2f> operator()(const Image2Grey& img_in, Sobel_t type=GRAD_33) const;

private:

    Vec2f _directionOf3(const Image2Grey& img_in, int x, int y) const;
    Vec2f _directionOf5(const Image2Grey& img_in, int x, int y) const;

    static const int Sobel5x[25];
    static const int Sobel5y[25];

    static const int Sobel3x[9];
    static const int Sobel3y[9];
};

#endif // IMGGRADIENT_H
