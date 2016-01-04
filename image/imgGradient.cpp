#include "imgGradient.h"

//====================================================================================================================================
//Constantes//

const int GradientSobel::Sobel5x[25]={1,2,0,-2,-1,
                                      4,8,0,-8,-4,
                                      6,12,0,-12,-6,
                                      4,8,0,-8,-4,
                                      1,2,0,-2,-1};

const int GradientSobel::Sobel5y[25]={1, 4, 6, 4, 1,
                                      2, 8, 12, 8, 2,
                                      0, 0, 0, 0, 0,
                                      -2,-8,-12,-8,-2,
                                      -1,-4,-6,-4,-1};

const int GradientSobel::Sobel3x[9]={-1,0, 1,
                                     -2,0, 2,
                                     -1,0, 1};

const int GradientSobel::Sobel3y[9]={-1,-2,-1,
                                      0, 0, 0,
                                      1, 2, 1};

//====================================================================================================================================
//Constructeurs

GradientSobel::GradientSobel()
{}

//====================================================================================================================================
//Autres

Vec2f GradientSobel::_directionOf3(const Image2Grey& img_in, int x, int y) const
{
    int w=(int)img_in.getWidth(), h=(int)img_in.getHeight();
    Vec2f result(0,0);
    int gXValue, gYValue, kx=0, ky=0;
    unsigned char pixel;
    for(int i=x-1; i<=x+1; i++)
    {
        if(i>=0 && i<w)
            for(int j=y-1; j<=y+1; j++)
            {
                if(j>=0 && j<h)
                {
                    int k=kx+(3*ky);
                    gXValue=Sobel3x[k];
                    gYValue=Sobel3y[k];
                    pixel=img_in.getPixel((unsigned int)i,(unsigned int)j);
                    result.setX(result.X()+gXValue*pixel);
                    result.setY(result.Y()+gYValue*pixel);
                }
                ++ky;
            }
        ++kx;
        ky=0;
    }
    return result;
}

Vec2f GradientSobel::_directionOf5(const Image2Grey& img_in, int x, int y) const
{
    int w=(int)img_in.getWidth(), h=(int)img_in.getHeight();
    Vec2f result(0,0);
    int gXValue, gYValue, kx=0, ky=0;
    unsigned char pixel;
    for(int i=x-2; i<=x+2; i++)
    {
        if(i>=0 && i<w)
            for(int j=y-2; j<=y+2; j++)
            {
                if(j>=0 && j<h)
                {
                    int k=kx+(5*ky);
                    gXValue=Sobel5x[k];
                    gYValue=Sobel5y[k];
                    pixel=img_in.getPixel((unsigned int)i,(unsigned int)j);
                    result.setX(result.X()+gXValue*pixel);
                    result.setY(result.Y()+gYValue*pixel);
                }
                ++ky;
            }
        ++kx;
        ky=0;
    }
    return result;
}

Image2<Vec2f> GradientSobel::gradient33(const Image2Grey& img_in) const
{
    Image2<Vec2f> img_out(img_in.getWidth(), img_in.getHeight());
    for(unsigned int x=0; x<img_in.getWidth(); x++)
    {
        for(unsigned int y=0; y<img_in.getHeight(); y++)
        {
            img_out.setPixel(_directionOf3(img_in, (int)x, (int)y), x, y);
        }
    }
    return img_out;
}

Image2<Vec2f> GradientSobel::gradient55(const Image2Grey& img_in) const
{
    Image2<Vec2f> img_out(img_in.getWidth(), img_in.getHeight());
    for(unsigned int x=0; x<img_in.getWidth(); x++)
    {
        for(unsigned int y=0; y<img_in.getHeight(); y++)
        {
            img_out.setPixel(_directionOf5(img_in, (int)x, (int)y), x, y);
        }
    }
    return img_out;
}

Image2<Vec2f> GradientSobel::operator()(const Image2Grey& img_in, Sobel_t type) const
{
    switch(type)
    {
        case GRAD_33:
            return gradient33(img_in);
            break;
        case GRAD_55:
            return gradient55(img_in);
            break;
        default:
            break;
    }
    return gradient33(img_in);
}
