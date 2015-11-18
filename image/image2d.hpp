#ifndef IMAGE2D_HPP
#define IMAGE2D_HPP

#include <iostream>
#include <cstdio>
#include <cstring>
#include <stdexcept>

template<typename T> class Image2D
{
public:

    //Constructeurs//

    Image2D();

    Image2D(const Image2D<T> &other);

    Image2D(size_t width, size_t height);

    virtual ~Image2D();

    //Opérateurs//

    Image2D& operator=(const Image2D<T> &other);

    //Accesseurs//

    T& getPixel(unsigned int i, unsigned int j) const;

    void setPixel(const T& pixel, unsigned int i, unsigned int j);

    size_t getWidth() const;

    size_t getHeight() const;

    const T* getArray() const;

    //Opérations//

    void exchangeWith(Image2D<T> &other); //pourquoi faire ? TODO

    //Image2D<T> crop(int start, int finish) ?? TODO

protected:

    size_t m_width;
    size_t m_height;
    T *m_tab;

};

//====================================================================================================================================
//Constructeurs//

template<typename T>
Image2D<T>::Image2D() :
    m_width(0), m_height(0), m_tab(0)
{}

template<typename T>
Image2D<T>::Image2D(const Image2D<T> &other) :
    m_width(other.getWidth()), m_height(other.getHeight()), m_tab(new T[m_width*m_height])
{
    memcpy(m_tab,other.getArray(),m_width*m_height*sizeof(T));
}

template<typename T>
Image2D<T>::Image2D(size_t width, size_t height) :
    m_width(width), m_height(height), m_tab(new T[m_width*m_height])
{}

template<typename T>
Image2D<T>::~Image2D()
{
    delete m_tab;
}

//====================================================================================================================================
//Opérateurs//

template<typename T>
Image2D<T>& Image2D<T>::operator=(const Image2D<T> &other)
{
    //TODO : gestion des pointeurs avec operator= ?
    m_tab=other.getArray();
    m_width=other.getWidth();
    m_height=other.getHeight();
    return (*this);
}

//====================================================================================================================================
//Accesseurs//

template<typename T>
T& Image2D<T>::getPixel(unsigned int i, unsigned int j) const
{
    if(i>=m_width || j>=m_height)
        throw std::out_of_range("argument out of bounds");
    return m_tab[j*m_width+i];
}

//====================================================================================================================================

template<typename T>
void Image2D<T>::setPixel(const T& pixel, unsigned int i, unsigned int j)
{
    if(i>=m_width || j>=m_height)
        throw std::out_of_range("argument out of bounds");
    m_tab[j*m_width+i]=pixel;
}

//====================================================================================================================================

template<typename T>
size_t Image2D<T>::getWidth() const
{
    return m_width;
}

//====================================================================================================================================

template<typename T>
size_t Image2D<T>::getHeight() const
{
    return m_height;
}

//====================================================================================================================================

template<typename T>
const T* Image2D<T>::getArray() const
{
    return m_tab;
}

//====================================================================================================================================
//Opérations//

template<typename T>
void Image2D<T>::exchangeWith(Image2D<T> &other)
{

}

#endif // IMAGE2D_HPP
