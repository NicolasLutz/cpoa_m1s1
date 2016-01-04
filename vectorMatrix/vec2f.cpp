#include "vec2f.h"

//====================================================================================================================================
//Constructeurs
Vec2f::Vec2f() : Vector<2, float>()
{}

Vec2f::Vec2f(float x, float y) : Vector<2, float>()
{
    m_tab[0]=x;
    m_tab[1]=y;
}

Vec2f::Vec2f(const Vec2f& other) : Vector<2, float>(other)
{}

Vec2f::~Vec2f()
{

}

//====================================================================================================================================
//Opérateurs

Vec2f Vec2f::operator+(const Vec2f& other) const
{
    Vec2f v(other.X()+X(), other.Y()+Y());
    return v;
}

float Vec2f::operator*(const Vec2f& other) const
{
    return X()*other.X()+Y()*other.Y();
}

const Vec2f& Vec2f::operator*=(float fValue)
{
    setX(X()*fValue);
    setY(Y()*fValue);
    return (*this);
}

const Vec2f& Vec2f::operator*=(unsigned int uiValue)
{
    setX(X()*uiValue);
    setY(Y()*uiValue);
    return (*this);
}

const Vec2f& Vec2f::operator*=(int iValue)
{
    setX(X()*iValue);
    setY(Y()*iValue);
    return (*this);
}

const Vec2f& Vec2f::operator*=(double lfValue)
{
    setX(X()*lfValue);
    setY(Y()*lfValue);
    return (*this);
}

const Vec2f& Vec2f::operator*=(long int liValue)
{
    setX(X()*liValue);
    setY(Y()*liValue);
    return (*this);
}

Vec2f Vec2f::operator*(float fValue) const
{
    Vec2f v;
    v.setX(X()*fValue);
    v.setY(Y()*fValue);
    return v;
}

Vec2f Vec2f::operator*(unsigned int uiValue) const
{
    Vec2f v;
    v.setX(X()*uiValue);
    v.setY(Y()*uiValue);
    return v;
}

Vec2f Vec2f::operator*(int iValue) const
{
    Vec2f v;
    v.setX(X()*iValue);
    v.setY(Y()*iValue);
    return v;
}

Vec2f Vec2f::operator*(double lfValue) const
{
    Vec2f v;
    v.setX(X()*lfValue);
    v.setY(Y()*lfValue);
    return v;
}

Vec2f Vec2f::operator*(long int liValue) const
{
    Vec2f v;
    v.setX(X()*liValue);
    v.setY(Y()*liValue);
    return v;
}


//====================================================================================================================================
//Accesseurs

const float& Vec2f::X() const
{
    return m_tab[0];
}

//====================================================================================================================================

const float& Vec2f::Y() const
{
    return m_tab[1];
}

//====================================================================================================================================
//Accesseurs

void Vec2f::setX(float x)
{
    m_tab[0]=x;
}

void Vec2f::setY(float y)
{
    m_tab[1]=y;
}
