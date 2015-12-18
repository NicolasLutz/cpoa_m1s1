#include "boundingbox.h"

//----------------------------------------------------------------------------
//Constructeurs//

BoundingBox::BoundingBox() :
    m_xy1xy2()
{}

BoundingBox::BoundingBox(const BoundingBox &other) :
    m_xy1xy2(other.XY1(), other.XY2())
{}

BoundingBox::BoundingBox(float x1, float y1, float x2, float y2) :
    m_xy1xy2(Vec2f(x1, y1), Vec2f(x2, y2))
{}

BoundingBox::BoundingBox(const std::pair<Vec2f, Vec2f>& xy1xy2) :
    m_xy1xy2(xy1xy2)
{}

//----------------------------------------------------------------------------
//Accesseurs//

const Vec2f& BoundingBox::XY1() const
{
    return m_xy1xy2.first;
}

const float& BoundingBox::X1() const
{
    return m_xy1xy2.first.X();
}

const float& BoundingBox::Y1() const
{
    return m_xy1xy2.first.Y();
}

//----------------------------------------------------------------------------

const Vec2f& BoundingBox::XY2() const
{
    return m_xy1xy2.second;
}

const float& BoundingBox::X2() const
{
    return m_xy1xy2.second.X();
}

const float& BoundingBox::Y2() const
{
    return m_xy1xy2.second.Y();
}

//----------------------------------------------------------------------------
//Setteurs//

void BoundingBox::setXY1(const Vec2f &XY)
{
    m_xy1xy2.first=XY;
}

void BoundingBox::setX1(float x)
{
    m_xy1xy2.first.setX(x);
}

void BoundingBox::setY1(float y)
{
    m_xy1xy2.first.setY(y);
}

//----------------------------------------------------------------------------

void BoundingBox::setXY2(const Vec2f &XY)
{
    m_xy1xy2.second=XY;
}

void BoundingBox::setX2(float x)
{
    m_xy1xy2.second.setX(x);
}

void BoundingBox::setY2(float y)
{
    m_xy1xy2.second.setY(y);
}

//----------------------------------------------------------------------------
//Opérateurs//

BoundingBox BoundingBox::operator+(const BoundingBox &other) const
{
    float x1=std::min<float>(X1(), other.X1());
    float y1=std::min<float>(Y1(), other.Y1());
    float x2=std::max<float>(X2(), other.X2());
    float y2=std::max<float>(Y2(), other.Y2());
    return BoundingBox(x1, y1, x2, y2);
}

BoundingBox BoundingBox::operator-(const BoundingBox &other) const
{
    BoundingBox bd(*this);
    bool tall=false, eTooBig=false;
    if(other.Y1()<=Y1() && other.Y2()>=Y2())
    {//La boite est plus haute que this
        if(other.X2()>=X1() && other.X1()<=X1())
        {//La boite intersecte la partie gauche de this
            tall=true;
            bd.setX1(other.X2());
        }
        if(other.X1()<=X2() && other.X2()>=X2())
        {//La boite intersecte la partie droite de this
            if(tall)
            {//La boite intersecte la partie gauche de this, la partie droite et est plus haute
                eTooBig=true;
            }
            else
            {//La boite intersecte seulement la partie droite de this
                bd.setX2(other.X1());
            }
        }
    }
    else if(other.X1()<=X1() && other.X2()>=X2())
    {//La boite est plus large que this
        if(other.Y2()>=Y1() && other.Y1()<=Y1())
        {//La boite intersecte la partie basse de this
            bd.setY1(other.Y2());
        }
        else if(other.Y1()<=Y2() && other.Y2()>=Y2())
        {//La boite intersecte la partie haute de this
            bd.setY2(other.Y1());
        }
    }
    if(eTooBig)
    {
        bd.setXY1(Vec2f(0, 0));
        bd.setXY2(Vec2f(0, 0));
    }
    return bd;
}

BoundingBox BoundingBox::operator^(const BoundingBox &other) const
{
    BoundingBox bd;
    if(collides(other))
    {
        bd.setX1(std::max(X1(), other.X1()));
        bd.setY1(std::max(Y1(), other.Y1()));
        bd.setX2(std::min(X2(), other.X2()));
        bd.setY2(std::min(Y2(), other.Y2()));
    }
    return bd;
}


//----------------------------------------------------------------------------
//Opérations//

bool BoundingBox::collides(const BoundingBox &other) const
{
    return (std::abs(X1() - other.X1()) * 2 < std::abs(X1()-X2())+std::abs(other.X1()-other.X2()) &&
            (std::abs(Y1() - other.Y1()) * 2 < std::abs(Y1()-Y2())+std::abs(other.Y1()-other.Y2())));
}
