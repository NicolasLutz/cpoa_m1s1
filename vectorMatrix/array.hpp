#ifndef ARRAY_H
#define ARRAY_H

#include <stdexcept>
#include <iostream>

#define _e_ 0.01 //floating point authorized error for null check

template<int size, typename T> class Array
{
public:

    //Constructeurs//

    Array();

    Array(const Array<size,T> &other);

    //Opérateurs//

    Array& operator=(const Array<size,T> &other);

    T& operator[](int i);

    bool operator==(const Array<size,T> &other) const;

    //Accesseurs//

    const T& getElement(int i) const; //read-only assignement

    int getSize() const;

    //Opérations//

    void exchangeWith(Array<size,T> &other);

protected://débatable ? TODO

    T m_tab[size];

};

template<int size, typename T>
std::ostream& operator<< (std::ostream &stream, const Array<size,T> &array);

//------------------------------------------------
//------------------------------------------------

//====================================================================================================================================
//Constructeurs//

template<int size, typename T>
Array<size,T>::Array()
{}

//====================================================================================================================================

template<int size, typename T>
Array<size,T>::Array(const Array<size,T> &other)
{
    for(int i=0; i<size && i<size; i++)
    {
        m_tab[i]=other.getElement(i);
    }
}

//====================================================================================================================================
//Opérateurs//

template<int size, typename T>
Array<size,T>& Array<size,T>::operator=(const Array<size, T> &other)
{
    for(int i=0; i<size && i<size; i++)
    {
        m_tab[i]=other.getElement(i);
    }
    return *(this);
}

//====================================================================================================================================

template<int size, typename T>
T& Array<size,T>::operator[](int i)
{
    if(i>=size || i<0)
    {
         throw std::out_of_range("argument out of bounds");
    }
    return m_tab[i];
}

//====================================================================================================================================

template<int size, typename T>
bool Array<size,T>::operator==(const Array<size,T> &other) const
{
    bool ret=true;
    for(int i=0;i<size && ret;i++)
    {
        if(m_tab[i]!=other.getElement(i))
            ret=false;
    }
    return ret;
}

//====================================================================================================================================
//Accesseurs//

template<int size, typename T>
int Array<size,T>::getSize() const
{
    return size;
}

template<int size, typename T>
const T& Array<size,T>::getElement(int i) const
{
    if(i<size)
        return m_tab[i];
    else
        throw std::out_of_range("argument out of bounds");
}

//====================================================================================================================================
//Opérations//

template<int size, typename T>
void Array<size,T>::exchangeWith(Array<size,T> &other)
{
    Array<size,T> copy;
    copy=other;
    for(int i=0;i<size;i++)
    {
        other[i]=m_tab[i];
        m_tab[i]=copy[i];
    }
}

//====================================================================================================================================
//Autres//

template<int size, typename T>
std::ostream& operator << (std::ostream &stream, const Array<size,T> &array)
{
    int i;
    stream << '[';
    for(i=0; i<(size-1); i++)
    {
        stream << array.getElement(i) << ", ";
    }
    if(i<size)
        stream << array.getElement(i);
    stream << ']';
    return stream;
}

//====================================================================================================================================


#endif // ARRAY_H
