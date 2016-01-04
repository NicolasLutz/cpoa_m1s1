#ifndef Image2D_US_UNKNOWNSIZE_HPP
#define Image2D_US_UNKNOWNSIZE_HPP

#ifndef Image2D_US_HPP
#define Image2D_US_HPP

#include <iostream>
#include <cstdio>
#include <cstring>
#include <stdexcept>
#include "vec2f.h"

template<typename T> class Image2 //US stands for unknown size
{
public:

    //Constructeurs//

    Image2();

    Image2(const Image2<T> &other);

    Image2(size_t width, size_t height);

    virtual ~Image2();

    //Opérateurs//

    Image2& operator=(const Image2<T> &other);

    //Accesseurs//

    T& getPixel(unsigned int i, unsigned int j) const;

    void setPixel(const T& pixel, unsigned int i, unsigned int j);

    size_t getWidth() const;

    size_t getHeight() const;

    T* getArray() const;

    //Opérations//

    void clear();

    //Itérateurs//

    class iterator_bbox
    {
    public:
        typedef iterator_bbox self_type;
        typedef int difference_type;
        typedef T value_type;
        typedef T* pointer;
        typedef T& reference;
        typedef std::forward_iterator_tag iterator_category;

        iterator_bbox() {}
        iterator_bbox(value_type* ptr);
        iterator_bbox(value_type* ptr,
                      unsigned int xStart, unsigned int xStop,
                      unsigned int yStart, size_t width);

        self_type operator=(const self_type& other);
        self_type operator++();
        self_type operator++(int unusued);
        value_type& operator*();
        value_type* operator->();
        bool operator==(const self_type& other);
        bool operator!=(const self_type& other);

        //Hors interface//
        Vec2f Vertice(); ///< returns the vertice in img coordinates

    private:
        value_type*     m_ptr;
        unsigned int    m_xStart; ///< at which x are we supposed to start?
        unsigned int    m_xStop; ///< at which x is the box's edge?
        size_t          m_spaceBetweenLines; ///< used for jumping to another line
        unsigned int    m_xIndex;
        unsigned int    m_yIndex;
    };

    iterator_bbox begin();
    iterator_bbox end();

    iterator_bbox beginOf(int xStart, int xStop, int yStart);
    iterator_bbox endOf(int xStop, int yStop);

    //Const itérateur//
    class const_iterator_bbox
    {
    public:
        typedef const_iterator_bbox self_type;
        typedef int difference_type;
        typedef T value_type;
        typedef T* pointer;
        typedef T& reference;
        typedef std::forward_iterator_tag iterator_category;

        const_iterator_bbox() {}
        const_iterator_bbox(const value_type* ptr);
        const_iterator_bbox(const value_type* ptr,
                      unsigned int xStart, unsigned int xStop,
                      unsigned int yStart, size_t width);

        self_type operator=(const self_type& other);
        self_type operator++();
        self_type operator++(int unusued);
        const value_type& operator*();
        const value_type* operator->();
        bool operator==(const self_type& other);
        bool operator!=(const self_type& other);

        //Hors interface//
        Vec2f Vertice();

    private:
        const value_type*   m_ptr;
        unsigned int        m_xStart; ///< at which x are we supposed to start?
        unsigned int        m_xStop; ///< at which x is the box's edge?
        size_t              m_spaceBetweenLines; ///< used for jumping to another line
        unsigned int        m_xIndex;
        unsigned int        m_yIndex;
    };

    const_iterator_bbox begin() const;
    const_iterator_bbox end() const;

    const_iterator_bbox beginOf(int xStart, int xStop, int yStart) const;
    const_iterator_bbox endOf(int xStop, int yStop) const;

protected:

    size_t m_width;
    size_t m_height;
    T *m_tab;

};

//====================================================================================================================================
//Constructeurs//

template<typename T>
Image2<T>::Image2() :
    m_width(0), m_height(0), m_tab(0)
{}

template<typename T>
Image2<T>::Image2(const Image2<T> &other) :
    m_width(other.getWidth()), m_height(other.getHeight()), m_tab(new T[m_width*m_height])
{
    memcpy(m_tab,other.getArray(),m_width*m_height*sizeof(T));
}

template<typename T>
Image2<T>::Image2(size_t width, size_t height) :
    m_width(width), m_height(height), m_tab(new T[m_width*m_height])
{}

template<typename T>
Image2<T>::~Image2()
{
    //delete m_tab;
}

//====================================================================================================================================
//Opérateurs//

template<typename T>
Image2<T>& Image2<T>::operator=(const Image2<T> &other)
{
    //TODO : gestion des pointeurs avec operator= ?
    memcpy(m_tab,other.getArray(),m_width*m_height*sizeof(T));
    m_width=other.getWidth();
    m_height=other.getHeight();
    return (*this);
}

//====================================================================================================================================
//Accesseurs//

template<typename T>
T& Image2<T>::getPixel(unsigned int i, unsigned int j) const
{
    return m_tab[j*m_width+i];
}

//====================================================================================================================================

template<typename T>
void Image2<T>::setPixel(const T& pixel, unsigned int i, unsigned int j)
{
    m_tab[j*m_width+i]=pixel;
}

//====================================================================================================================================

template<typename T>
size_t Image2<T>::getWidth() const
{
    return m_width;
}

//====================================================================================================================================

template<typename T>
size_t Image2<T>::getHeight() const
{
    return m_height;
}

//====================================================================================================================================

template<typename T>
T* Image2<T>::getArray() const
{
    return m_tab;
}

//====================================================================================================================================
//Itérateurs//

template<typename T>
void Image2<T>::clear()
{
    iterator_bbox end=this->end();
    for(iterator_bbox it=begin();it!=end;++it)
    {
        *it=T(0);
    }
}

//====================================================================================================================================
//Itérateurs//

template<typename T>
typename Image2<T>::iterator_bbox Image2<T>::begin()
{
    iterator_bbox it(m_tab, 0, m_width-1, 0, m_width);
    return it;
}

template<typename T>
typename Image2<T>::iterator_bbox Image2<T>::end()
{
    iterator_bbox it(m_tab+(m_height*m_width));
    return it;
}

template<typename T>
typename Image2<T>::iterator_bbox Image2<T>::beginOf(int xStart, int xStop, int yStart)
{
    unsigned int validXStart=std::max(0, std::min(xStart, (int)m_width-1));
    unsigned int validXStop=std::max(0, std::min(xStop, (int)m_width-1));
    unsigned int validYStart=std::max(0, std::min(yStart, (int)m_height-1));
    iterator_bbox it(m_tab+(validYStart*m_width)+validXStart, validXStart, validXStop, validYStart, m_width);
    return it;
}

template<typename T>
typename Image2<T>::iterator_bbox Image2<T>::endOf(int xStop, int yStop)
{
    unsigned int validXStop=std::max(0, std::min(xStop, (int)m_width-1));
    unsigned int validYStop=std::max(0, std::min(yStop, (int)m_height-1));
    iterator_bbox it(m_tab+(validYStop*m_width)+validXStop+1);
    return it;
}

//====================================================================================================================================
//Const Itérateur//

template<typename T>
typename Image2<T>::const_iterator_bbox Image2<T>::begin() const
{
    const_iterator_bbox it(m_tab, 0, m_width-1, 0, m_width);
    return it;
}

template<typename T>
typename Image2<T>::const_iterator_bbox Image2<T>::end() const
{
    const_iterator_bbox it(m_tab+(m_height*m_width));
    return it;
}

template<typename T>
typename Image2<T>::const_iterator_bbox Image2<T>::beginOf(int xStart, int xStop, int yStart) const
{
    unsigned int validXStart=std::max(0, std::min(xStart, (int)m_width-1));
    unsigned int validXStop=std::max(0, std::min(xStop, (int)m_width-1));
    unsigned int validYStart=std::max(0, std::min(yStart, (int)m_height-1));
    const_iterator_bbox it(m_tab+(validYStart*m_width)+validXStart, validXStart, validXStop, validYStart, m_width);
    return it;
}

template<typename T>
typename Image2<T>::const_iterator_bbox Image2<T>::endOf(int xStop, int yStop) const
{
    unsigned int validXStop=std::max(0, std::min(xStop, (int)m_width-1));
    unsigned int validYStop=std::max(0, std::min(yStop, (int)m_height-1));
    const_iterator_bbox it(m_tab+(validYStop*m_width)+validXStop+1);
    return it;
}

//====================================================================================================================================
//====================================================================================================================================
//Image2<T>::Itérateur//

template<typename T>
Image2<T>::iterator_bbox::iterator_bbox(value_type* ptr):
    m_ptr(ptr)
{}

template<typename T>
Image2<T>::iterator_bbox::iterator_bbox(value_type* ptr, unsigned int xStart, unsigned int xStop,
                                         unsigned int yStart, size_t width):
  m_ptr(ptr)
, m_xStart(xStart)
, m_xStop(xStop)
, m_spaceBetweenLines((width-m_xStop)+m_xStart)
, m_xIndex(xStart)
, m_yIndex(yStart)
{}

template<typename T>
typename Image2<T>::iterator_bbox::self_type Image2<T>::iterator_bbox::operator=(const self_type& other)
{
    m_ptr = other.m_ptr;
    m_xStart=other.m_xStart;
    m_xStop=other.m_xStop;
    m_spaceBetweenLines=other.m_spaceBetweenLines;
    m_xIndex=other.m_xIndex;
    m_yIndex=other.m_yIndex;
    return *this;
}

template<typename T>
typename Image2<T>::iterator_bbox::self_type Image2<T>::iterator_bbox::operator++()
{
    if(m_xIndex==m_xStop)
    {
        m_xIndex=m_xStart;
        m_ptr+=m_spaceBetweenLines;
        m_yIndex++;
    }
    else
    {
        m_xIndex++;
        m_ptr++;
    }
    return *this;
}

template<typename T>
typename Image2<T>::iterator_bbox::self_type Image2<T>::iterator_bbox::operator++(int unusued)
{
    iterator_bbox i=*this;
    if(m_xIndex==m_xStop)
    {
        m_xIndex=m_xStart;
        m_ptr+=m_spaceBetweenLines;
        m_yIndex++;
    }
    else
    {
        m_xIndex++;
        m_ptr++;
    }
    return i;
}

template<typename T>
typename Image2<T>::iterator_bbox::value_type& Image2<T>::iterator_bbox::operator*()
{
    return *m_ptr;
}

template<typename T>
typename Image2<T>::iterator_bbox::value_type* Image2<T>::iterator_bbox::operator->()
{
    return m_ptr;
}

template<typename T>
bool Image2<T>::iterator_bbox::operator==(const self_type& other)
{
    return m_ptr == other.m_ptr;
}

template<typename T>
bool Image2<T>::iterator_bbox::operator!=(const self_type& other)
{
    return m_ptr < other.m_ptr;
}

template<typename T>
Vec2f Image2<T>::iterator_bbox::Vertice()
{
    Vec2f v((float)m_xIndex, (float)m_yIndex);
    return v;
}


//====================================================================================================================================
//====================================================================================================================================
//Image2<T>::Const Itérateur//

template<typename T>
Image2<T>::const_iterator_bbox::const_iterator_bbox(const value_type* ptr):
    m_ptr(ptr)
{}

template<typename T>
Image2<T>::const_iterator_bbox::const_iterator_bbox(const value_type* ptr, unsigned int xStart, unsigned int xStop, unsigned int yStart, size_t width):
  m_ptr(ptr)
, m_xStart(xStart)
, m_xStop(xStop)
, m_spaceBetweenLines((width-m_xStop)+m_xStart)
, m_xIndex(xStart)
, m_yIndex(yStart)
{}

template<typename T>
typename Image2<T>::const_iterator_bbox::self_type Image2<T>::const_iterator_bbox::operator=(const self_type& other)
{
    m_ptr = other.m_ptr;
    m_xStart=other.m_xStart;
    m_xStop=other.m_xStop;
    m_spaceBetweenLines=other.m_spaceBetweenLines;
    m_xIndex=other.m_xIndex;
    m_yIndex=other.m_yIndex;
    return *this;
}

template<typename T>
typename Image2<T>::const_iterator_bbox::self_type Image2<T>::const_iterator_bbox::operator++()
{
    if(m_xIndex==m_xStop)
    {
        m_xIndex=m_xStart;
        m_ptr+=m_spaceBetweenLines;
        m_yIndex++;
    }
    else
    {
        m_xIndex++;
        m_ptr++;
    }
    return *this;
}

template<typename T>
typename Image2<T>::const_iterator_bbox::self_type Image2<T>::const_iterator_bbox::operator++(int unusued)
{
    const_iterator_bbox i=*this;
    if(m_xIndex==m_xStop)
    {
        m_xIndex=m_xStart;
        m_ptr+=m_spaceBetweenLines;
        m_yIndex++;
    }
    else
    {
        m_xIndex++;
        m_ptr++;
    }
    return i;
}

template<typename T>
const typename Image2<T>::const_iterator_bbox::value_type& Image2<T>::const_iterator_bbox::operator*()
{
    return *m_ptr;
}

template<typename T>
const typename Image2<T>::const_iterator_bbox::value_type* Image2<T>::const_iterator_bbox::operator->()
{
    return m_ptr;
}

template<typename T>
bool Image2<T>::const_iterator_bbox::operator==(const self_type& other)
{
    return m_ptr == other.m_ptr;
}

template<typename T>
bool Image2<T>::const_iterator_bbox::operator!=(const self_type& other)
{
    return m_ptr < other.m_ptr;
}

template<typename T>
Vec2f Image2<T>::const_iterator_bbox::Vertice()
{
    Vec2f v((float)m_xIndex, (float)m_yIndex);
    return v;
}



#endif // Image2D_US_HPP


#endif // Image2D_US_UNKNOWNSIZE_HPP
