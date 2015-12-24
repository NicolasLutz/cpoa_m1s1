#ifndef IMAGE2D_HPP
#define IMAGE2D_HPP

#include <iostream>
#include <cstdio>
#include <cstring>
#include <stdexcept>
#include <iterator>
#include "array.hpp"

template<size_t width, size_t height, typename T> class Image2D : public Array<width*height, T>
{
public:

    //Constructeurs//

    Image2D();

    Image2D(const Image2D<width, height, T> &other);

    virtual ~Image2D();

    //Opérateurs//

    Image2D& operator=(const Image2D<width, height, T> &other);

    //Accesseurs//

    T& getPixel(unsigned int i, unsigned int j) const;

    void setPixel(const T& pixel, unsigned int i, unsigned int j);

    //Opérations//

    void exchangeWith(Image2D<width, height, T> &other); //pourquoi faire ? TODO

    //Image2D<width, height, T> crop(int start, int finish) ?? TODO

};

//====================================================================================================================================
//Constructeurs//

template<size_t width, size_t height, typename T>
Image2D<width, height, T>::Image2D() :
    Array<width*height, T>()
{}

template<size_t width, size_t height, typename T>
Image2D<width, height, T>::Image2D(const Image2D<width, height, T> &other) :
    Array<width*height, T>(other)
{}

template<size_t width, size_t height, typename T>
Image2D<width, height, T>::~Image2D()
{}

//====================================================================================================================================
//Accesseurs//

template<size_t width, size_t height, typename T>
T& Image2D<width, height, T>::getPixel(unsigned int i, unsigned int j) const
{
    return operator[](j*m_width+i);
}

//====================================================================================================================================

template<size_t width, size_t height, typename T>
void Image2D<width, height, T>::setPixel(const T& pixel, unsigned int i, unsigned int j)
{
   return operator[](j*m_width+i)=pixel;
}

//====================================================================================================================================
//Opérations//

template<size_t width, size_t height, typename T>
void Image2D<width, height, T>::exchangeWith(Image2D<width, height, T> &other)
{

}

#endif // IMAGE2D_HPP
