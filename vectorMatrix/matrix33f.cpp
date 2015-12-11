#include "matrix33f.h"

#define _e_ (0.01f)

//====================================================================================================================================
//Constructeurs

Matrix33f::Matrix33f() : Array<3, Vec3f>()
{

}

Matrix33f::Matrix33f(const Matrix33f &other) : Array<3, Vec3f>(other)
{

}

//====================================================================================================================================
//Opérateurs

Vec3f Matrix33f::operator*(const Vec3f& vector) const
{
    Vec3f result;
    result.setX(m_tab[0].X()*vector.X()+m_tab[0].Y()*vector.Y()+m_tab[0].Z()*vector.Z());
    result.setY(m_tab[1].X()*vector.X()+m_tab[1].Y()*vector.Y()+m_tab[1].Z()*vector.Z());
    result.setZ(m_tab[2].X()*vector.X()+m_tab[2].Y()*vector.Y()+m_tab[2].Z()*vector.Z());
    return result;
}

//====================================================================================================================================
//Opérations

void Matrix33f::setInvert()
{
    Matrix33f m;
    //Le compilo devrait pouvoir optimiser ça
    float det   =m_tab[0].X()*(m_tab[1].Y()*m_tab[2].Z()-m_tab[2].Y()*m_tab[1].Z())
                -m_tab[0].Y()*(m_tab[1].X()*m_tab[2].Z()-m_tab[2].X()*m_tab[1].Z())
                +m_tab[0].Z()*(m_tab[1].X()*m_tab[2].Y()-m_tab[2].X()*m_tab[1].Y());
    if(det>_e_ || det<-_e_)//rappel : _e_ = epsilon pour erreur flottante
    {
        m[0][0]=(m_tab[1].Y() * m_tab[2].Z() - m_tab[2].Y() * m_tab[1].Z())/det;
        m[0][1]=-(m_tab[0].Y() * m_tab[2].Z() - m_tab[2].Y() * m_tab[0].Z())/det;
        m[0][2]=(m_tab[0].Y() * m_tab[1].Z() - m_tab[1].Y() * m_tab[0].Z())/det;

        m[1][0]=-(m_tab[1].X() * m_tab[2].Z() - m_tab[2].X() * m_tab[1].Z())/det;
        m[1][1]=(m_tab[0].X() * m_tab[2].Z() - m_tab[2].X() * m_tab[0].Z())/det;
        m[1][2]=-(m_tab[0].X() * m_tab[1].Z() - m_tab[1].X() * m_tab[0].Z())/det;

        m[2][0]=(m_tab[1].X() * m_tab[2].Y() - m_tab[2].X() * m_tab[1].Y())/det;
        m[2][1]=-(m_tab[0].X() * m_tab[2].Y() - m_tab[2].X() * m_tab[0].Y())/det;
        m[2][2]=(m_tab[0].X() * m_tab[1].Y() - m_tab[1].X() * m_tab[0].Y())/det;
        (*this)=m;
    }
}

//====================================================================================================================================

void Matrix33f::setId()
{
    m_tab[0][0]=1.0f;
    m_tab[0][1]=0;
    m_tab[0][2]=0;

    m_tab[1][0]=0;
    m_tab[1][1]=1.0f;
    m_tab[1][2]=0;

    m_tab[2][0]=0;
    m_tab[2][1]=0;
    m_tab[2][2]=1.0f;
}

//====================================================================================================================================

void Matrix33f::setTranslation(float tx, float ty)
{
    m_tab[0][0]=1.0f;
    m_tab[0][1]=0;
    m_tab[0][2]=tx;

    m_tab[1][0]=0;
    m_tab[1][1]=1.0f;
    m_tab[1][2]=ty;

    m_tab[2][0]=0;
    m_tab[2][1]=0;
    m_tab[2][2]=1.0f;
}

//====================================================================================================================================

void Matrix33f::setRotation(float rad)
{
    m_tab[0][0]=cos(rad);
    m_tab[0][1]=sin(rad);
    m_tab[0][2]=0;

    m_tab[1][0]=-sin(rad);
    m_tab[1][1]=cos(rad);
    m_tab[1][2]=0;

    m_tab[2][0]=0;
    m_tab[2][1]=0;
    m_tab[2][2]=1.0f;
}

//====================================================================================================================================

void Matrix33f::setScaling(float vx, float vy)
{
    m_tab[0][0]=vx;
    m_tab[0][1]=0;
    m_tab[0][2]=0;

    m_tab[1][0]=0;
    m_tab[1][1]=vy;
    m_tab[1][2]=0;

    m_tab[2][0]=0;
    m_tab[2][1]=0;
    m_tab[2][2]=1.0f;
}

//====================================================================================================================================
//Note : On suppose que les matrices ne contiennent pas de coordonnées "parasites"

void Matrix33f::addTranslation(float tx, float ty)
{
    m_tab[0][2]=m_tab[0][2]+tx;
    m_tab[1][2]=m_tab[1][2]+ty;
}

//====================================================================================================================================

void Matrix33f::addRotation(float rad)
{
    float cosinus=cos(rad);
    float sinus=sin(rad);
    //première ligne
    m_tab[0][0]=m_tab[0][0]*cosinus+m_tab[1][0]*sinus;
    m_tab[0][1]=m_tab[0][1]*cosinus+m_tab[1][1]*sinus;
    m_tab[0][2]=m_tab[0][2]*cosinus+m_tab[1][2]*sinus;

    //seconde ligne
    m_tab[1][0]=m_tab[0][0]*-sinus+m_tab[1][0]*cosinus;
    m_tab[1][1]=m_tab[0][1]*-sinus+m_tab[1][1]*cosinus;
    m_tab[1][2]=m_tab[0][2]*-sinus+m_tab[1][2]*cosinus;
}

//====================================================================================================================================

void Matrix33f::addScaling(float vx, float vy)
{
    //première ligne
    m_tab[0][0]*=vx;
    m_tab[0][1]*=vx;
    m_tab[0][2]*=vx;

    //seconde ligne
    m_tab[1][0]*=vy;
    m_tab[1][1]*=vy;
    m_tab[1][2]*=vy;
}

//====================================================================================================================================

void Matrix33f::apply(Vec2f &vector) const
{
    Vec3f vec3(vector, 1.0f);
    vec3=(*this)*vec3;
    vector.setX(vec3.X());
    vector.setY(vec3.Y());
}
