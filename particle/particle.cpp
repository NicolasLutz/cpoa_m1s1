#include "particle.h"

Vec2f Particle::s_gravity(0,0.405f);
int Particle::s_absoluteTime=0;
Matrix33f Particle::s_toTan(ROTATION_T, (M_PI/2));
Matrix33f Particle::s_toCounterTan(ROTATION_T, -(M_PI/2));

Particle::Particle()
{}

Particle::Particle(const Particle &other):
    m_c_velocity(other.getVelocity()), m_c_position(other.getPosition()), m_c_date(other.getDate()),
    m_f_velocity(other.getVelocity()), m_f_position(other.getPosition()), m_f_date(other.getDate()), m_startDate(other.getDate())
{}

Particle::Particle(const Vec2f& start, const Vec2f& velocity) :
    m_c_velocity(velocity), m_c_position(start), m_c_date(0),
    m_f_velocity(velocity), m_f_position(start), m_f_date(0), m_startDate(s_absoluteTime)
{}

//--------------------------------------------------------------------
//Opérations//

int Particle::update()
{
    int previousDate=getDate();
    while(m_f_position.distance(m_c_position) < 1.0f)
    {
        Vec2f position=m_f_position;
        Vec2f velocity=m_f_velocity;
        m_f_position=position+velocity+(s_gravity);
        m_f_velocity=velocity+(s_gravity);
        m_f_date++;
    }
    return m_f_date-previousDate;
}

void Particle::validate(const Image2Grey& img_in, const Image2<Vec2f> &img_grad)
{
    int x=m_f_position.X();
    int y=m_f_position.Y();
    if(x>=0 && x<(int)img_in.getWidth() && y>=0 && y < (int)img_in.getHeight())
    {
        unsigned char pixel=img_in.getPixel(x,y);
        if(pixel!=0 && img_grad.getArray()!=NULL)
        {
            _giveCollisionPoint(img_in, x, y);
            Vec2f& directionPixel=img_grad.getPixel(x, y);
            if(directionPixel.X()!=0 && directionPixel.Y()!=0)
            {
                Vec2f tan=(directionPixel.X()<0 ? s_toTan*directionPixel : s_toCounterTan*directionPixel);
                directionPixel.normalize();
                tan.normalize();
                m_f_velocity=directionPixel*-0.5 + tan*0.9;
                m_f_position+=m_f_velocity*(float)(m_f_date-m_c_date+1);
            }
        }
    }
    m_c_position=m_f_position;
    m_c_velocity=m_f_velocity;
    m_c_date=m_f_date;
}

//--------------------------------------------------------------------
//Accesseurs//

const Vec2f &Particle::getVelocity() const
{
    return m_c_velocity;
}

const Vec2f& Particle::getPosition() const
{
    return m_c_position;
}

int Particle::getDate() const
{
    return m_c_date;
}

int Particle::getPriority() const
{
    return m_c_date+m_startDate;
}

//--------------------------------------------------------------------
//Setters//

void Particle::addAbsoluteTime()
{
    s_absoluteTime++;
}

//--------------------------------------------------------------------
//Private//

void Particle::_giveCollisionPoint(const Image2Grey& img_in, int &x, int &y)
{
    int n=0;
    float steps=-m_f_velocity.Y();
    Vec2f acceleration=s_gravity;
    acceleration/=steps;
    while(img_in.getPixel(x, y)==0)
    {
        Vec2f velocity=m_c_velocity;
        velocity/=steps;
        m_f_position=m_c_position+velocity+acceleration;
        m_f_velocity=velocity+acceleration;
        x=m_f_position.X();
        y=m_f_position.Y();
        if(++n==(int)steps)
        {
            m_c_date++;
            n=0;
        }
    }
}
