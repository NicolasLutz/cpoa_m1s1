#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "array.hpp"

template<size_t size, typename T> class Vector : public Array<size, T>
{
public:

    //Constructeurs//

    Vector();

    Vector(const Vector<size, T> &vector);

    //Opérateurs

    Vector<size, T> operator+(const Vector<size, T> &other) const;
    Vector<size, T>& operator+=(const Vector<size, T> &other);

    Vector<size, T> operator-(const Vector<size, T> &other) const;
    Vector<size, T>& operator-=(const Vector<size, T> &other);

    Vector<size, T> operator*(T& s) const;
    Vector<size, T>& operator*=(T& s);

    Vector<size, T> operator/(T& s) const;
    Vector<size, T>& operator/=(T& s);
};

//------------------------------------------------
//------------------------------------------------

//====================================================================================================================================
//Constructeurs//

template<size_t size, typename T>
Vector<size, T>::Vector() : Array<size, T>()
{
}

template<size_t size, typename T>
Vector<size, T>::Vector(const Vector<size, T> &vector) : Array<size, T>(vector)
{}

//====================================================================================================================================
//Opérateurs//

template<size_t size, typename T>
Vector<size, T> Vector<size, T>::operator+(const Vector<size, T> &other) const
{
    Vector<size, T> v;
    for(unsigned int i=0; i<size; i++)
    {
        v[i]=this->m_tab[i]+other[i];
    }
    return v;
}

//====================================================================================================================================

template<size_t size, typename T>
Vector<size, T>& Vector<size, T>::operator+=(const Vector<size, T> &other)
{
    for(unsigned int i=0; i<size; i++)
    {
        this->m_tab[i]+=other[i];
    }
    return *(this);
}

//====================================================================================================================================

template<size_t size, typename T>
Vector<size, T> Vector<size, T>::operator-(const Vector<size, T> &other) const
{
    Vector<size, T> v;
    for(unsigned int i=0; i<size; i++)
    {
        v[i]=this->m_tab[i]-other[i];
    }
    return v;
}

//====================================================================================================================================

template<size_t size, typename T>
Vector<size, T>& Vector<size, T>::operator-=(const Vector<size, T> &other)
{
    for(unsigned int i=0; i<size; i++)
    {
        this->m_tab[i]-=other[i];
    }
    return *(this);
}

//====================================================================================================================================

template<size_t size, typename T>
Vector<size, T> Vector<size, T>::operator*(T& s) const
{
    Vector<size, T> v;
    for(unsigned int i=0; i<size; i++)
    {
        v[i]=this->m_tab[i]*s;
    }
    return v;
}

//====================================================================================================================================

template<size_t size, typename T>
Vector<size, T>& Vector<size, T>::operator*=(T& s)
{
    for(unsigned int i=0; i<size; i++)
    {
        this->m_tab[i]*=s;
    }
    return *(this);
}

//====================================================================================================================================

template<size_t size, typename T>
Vector<size, T> Vector<size, T>::operator/(T& s) const
{
    Vector<size, T> v;
    for(unsigned int i=0; i<size; i++)
    {
        v[i]=this->m_tab[i]/s;
    }
    return v;
}

//====================================================================================================================================

template<size_t size, typename T>
Vector<size, T>& Vector<size, T>::operator/=(T& s)
{
    for(unsigned int i=0; i<size; i++)
    {
        this->m_tab[i]/=s;
    }
    return *(this);
}

//====================================================================================================================================

#endif // VECTOR_HPP