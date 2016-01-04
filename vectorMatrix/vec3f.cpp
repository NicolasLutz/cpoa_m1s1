#include "vec3f.h"

//====================================================================================================================================
//Constructeurs
Vec3f::Vec3f() : Vector<3, float>()
{}

Vec3f::Vec3f(float x, float y, float z) : Vector<3, float>()
{
    m_tab[0]=x;
    m_tab[1]=y;
    m_tab[2]=z;
}

Vec3f::Vec3f(const Vec3f &other) : Vector<3, float>(other)
{}

Vec3f::Vec3f(const Vec2f &vector2, float z) : Vector<3, float>()
{
    m_tab[0]=vector2.X();
    m_tab[1]=vector2.Y();
    m_tab[2]=z;
}

//====================================================================================================================================
//Opérateurs

float Vec3f::operator*(const Vec3f& other) const
{
    return X()*other.X()+Y()*other.Y()+Z()*other.Z();
}

Vec3f Vec3f::operator^(const Vec3f& other) const
{
    Vec3f res(  Y()*other.Z()-Z()*other.Y()
               ,Z()*other.X()-X()*other.Z()
               ,X()*other.Y()-Y()*other.X());
    return res;
}

//====================================================================================================================================

const Vec3f& Vec3f::operator*=(float fValue)
{
    setX(X()*fValue);
    setY(Y()*fValue);
    setZ(Z()*fValue);
    return (*this);
}

const Vec3f& Vec3f::operator*=(unsigned int uiValue)
{
    setX(X()*uiValue);
    setY(Y()*uiValue);
    setZ(Z()*uiValue);
    return (*this);
}

const Vec3f& Vec3f::operator*=(int iValue)
{
    setX(X()*iValue);
    setY(Y()*iValue);
    setZ(Z()*iValue);
    return (*this);
}

const Vec3f& Vec3f::operator*=(double lfValue)
{
    setX(X()*lfValue);
    setY(Y()*lfValue);
    setZ(Z()*lfValue);
    return (*this);
}

const Vec3f& Vec3f::operator*=(long int liValue)
{
    setX(X()*liValue);
    setY(Y()*liValue);
    setZ(Z()*liValue);
    return (*this);
}

Vec3f Vec3f::operator*(float fValue) const
{
    Vec3f v;
    v.setX(X()*fValue);
    v.setY(Y()*fValue);
    v.setZ(Z()*fValue);
    return v;
}

Vec3f Vec3f::operator*(unsigned int uiValue) const
{
    Vec3f v;
    v.setX(X()*uiValue);
    v.setY(Y()*uiValue);
    v.setZ(Z()*uiValue);
    return v;
}

Vec3f Vec3f::operator*(int iValue) const
{
    Vec3f v;
    v.setX(X()*iValue);
    v.setY(Y()*iValue);
    v.setZ(Z()*iValue);
    return v;
}

Vec3f Vec3f::operator*(double lfValue) const
{
    Vec3f v;
    v.setX(X()*lfValue);
    v.setY(Y()*lfValue);
    v.setZ(Z()*lfValue);
    return v;
}

Vec3f Vec3f::operator*(long int liValue) const
{
    Vec3f v;
    v.setX(X()*liValue);
    v.setY(Y()*liValue);
    v.setZ(Z()*liValue);
    return v;
}

//Accesseurs

const float& Vec3f::X() const
{
    return m_tab[0];
}

const float& Vec3f::Y() const
{
    return m_tab[1];
}

const float& Vec3f::Z() const
{
    return m_tab[2];
}

Vec2f Vec3f::XY() const
{
    return Vec2f(X(),Y());
}

//====================================================================================================================================
//Setteurs

void Vec3f::setX(float x)
{
    m_tab[0]=x;
}

void Vec3f::setY(float y)
{
    m_tab[1]=y;
}

void Vec3f::setZ(float z)
{
    m_tab[2]=z;
}

//====================================================================================================================================
//Outside

Vec3f operator^(const Vec2f& v_this, const Vec2f& other)
{
    Vec3f res(0,0,v_this.X()*other.Y()-v_this.Y()*other.X());
    return res;
}
