#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "array.hpp"

template<int size> class Vector : public Array<size, float>
{
public:

    //Constructeurs//

    Vector();

    Vector(const Vector<size> &vector);

    //Opérateurs

    Vector<size> operator+(const Vector<size> &other) const;
    Vector<size>& operator+=(const Vector<size> &other);

    Vector<size> operator-(const Vector<size> &other) const;
    Vector<size>& operator-=(const Vector<size> &other);

    Vector<size> operator*(float s) const;
    Vector<size>& operator*=(float s);

    Vector<size> operator/(float s) const;
    Vector<size>& operator/=(float s);
};

//------------------------------------------------
//------------------------------------------------

//====================================================================================================================================
//Constructeurs//

template<int size>
Vector<size>::Vector() : Array<size,float>()
{
}

template<int size>
Vector<size>::Vector(const Vector<size> &vector) : Array<size, float>(vector)
{}

//====================================================================================================================================
//Opérateurs//

template<int size>
Vector<size> Vector<size>::operator+(const Vector<size> &other) const
{
    Vector<size> v;
    for(int i=0; i<size; i++)
    {
        v[i]=this->m_tab[i]+other.getElement(i);
    }
    return v;
}

//====================================================================================================================================

template<int size>
Vector<size>& Vector<size>::operator+=(const Vector<size> &other)
{
    for(int i=0; i<size; i++)
    {
        this->m_tab[i]+=other.getElement(i);
    }
    return *(this);
}

//====================================================================================================================================

template<int size>
Vector<size> Vector<size>::operator-(const Vector<size> &other) const
{
    Vector<size> v;
    for(int i=0; i<size; i++)
    {
        v[i]=this->m_tab[i]-other.getElement(i);
    }
    return v;
}

//====================================================================================================================================

template<int size>
Vector<size>& Vector<size>::operator-=(const Vector<size> &other)
{
    for(int i=0; i<size; i++)
    {
        this->m_tab[i]-=other.getElement(i);
    }
    return *(this);
}

//====================================================================================================================================

template<int size>
Vector<size> Vector<size>::operator*(float s) const
{
    Vector<size> v;
    for(int i=0; i<size; i++)
    {
        v[i]=this->m_tab[i]*s;
    }
    return v;
}

//====================================================================================================================================

template<int size>
Vector<size>& Vector<size>::operator*=(float s)
{
    for(int i=0; i<size; i++)
    {
        this->m_tab[i]*=s;
    }
    return *(this);
}

//====================================================================================================================================

template<int size>
Vector<size> Vector<size>::operator/(float s) const
{
    Vector<size> v;
    for(int i=0; i<size; i++)
    {
        v[i]=this->m_tab[i]/s;
    }
    return v;
}

//====================================================================================================================================

template<int size>
Vector<size>& Vector<size>::operator/=(float s)
{
    for(int i=0; i<size; i++)
    {
        this->m_tab[i]/=s;
    }
    return *(this);
}

//====================================================================================================================================

#endif // VECTOR_HPP
