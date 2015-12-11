#ifndef ARRAY_H
#define ARRAY_H

#include <stdexcept>
#include <iostream>

//#define _e_ 0.01 //floating point authorized error for null check

template<size_t size, typename T> class Array
{
public:

    //Constructeurs//

    Array();

    Array(const Array<size,T> &other);

    //Opérateurs//

    Array& operator=(const Array<size,T> &other);

    T& operator[](unsigned int i);

    const T& operator[](unsigned int i) const;

    bool operator==(const Array<size,T> &other) const;

    //Accesseurs//

    size_t Size() const;

    //Opérations//

    void exchangeWith(Array<size,T> &other);

protected://débatable ? TODO

    T m_tab[size];

};

template<size_t size, typename T>
std::ostream& operator<< (std::ostream &stream, const Array<size,T> &array);

//------------------------------------------------
//------------------------------------------------

//====================================================================================================================================
//Constructeurs//

template<size_t size, typename T>
Array<size,T>::Array()
{}

//====================================================================================================================================

template<size_t size, typename T>
Array<size,T>::Array(const Array<size,T> &other)
{
    for(unsigned int i=0; i<size; i++)
    {
        m_tab[i]=other[i];
    }
}

//====================================================================================================================================
//Opérateurs//

template<size_t size, typename T>
Array<size,T>& Array<size,T>::operator=(const Array<size, T> &other)
{
    for(unsigned int i=0; i<size; i++)
    {
        m_tab[i]=other[i];
    }
    return *(this);
}

//====================================================================================================================================

template<size_t size, typename T>
T& Array<size,T>::operator[](unsigned int i)
{
    if(i>=size || i<0)
    {
         throw std::out_of_range("argument out of bounds");
    }
    return m_tab[i];
}

template<size_t size, typename T>
const T& Array<size,T>::operator[](unsigned int i) const
{
    if(i>=size || i<0)
    {
         throw std::out_of_range("argument out of bounds");
    }
    return m_tab[i];
}

//====================================================================================================================================

template<size_t size, typename T>
bool Array<size,T>::operator==(const Array<size,T> &other) const
{
    bool ret=true;
    for(unsigned int i=0;i<size && ret;i++)
    {
        if(m_tab[i]!=other[i])
            ret=false;
    }
    return ret;
}

//====================================================================================================================================
//Accesseurs//

template<size_t size, typename T>
size_t Array<size, T>::Size() const
{
    return size;
}

//====================================================================================================================================
//Opérations//

template<size_t size, typename T>
void Array<size,T>::exchangeWith(Array<size,T> &other)
{
    Array<size,T> copy;
    copy=other;
    for(unsigned int i=0;i<size;i++)
    {
        other[i]=m_tab[i];
        m_tab[i]=copy[i];
    }
}

//====================================================================================================================================
//Autres//

template<size_t size, typename T>
std::ostream& operator << (std::ostream &stream, const Array<size,T> &array)
{
    unsigned int i;
    stream << '[';
    for(i=0; i<(size-1); i++)
    {
        stream << array[i] << ", ";
    }
    if(i<size)
        stream << array[i];
    stream << ']';
    return stream;
}

//====================================================================================================================================


#endif // ARRAY_H
