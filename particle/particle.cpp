#include "particle.h"

Vec2f Particle::s_gravity(0,1);
int Particle::s_absoluteTime=0;

Particle::Particle()
{}

Particle::Particle(const Particle &other):
    m_c_velocity(other.getVelocity()), m_c_position(other.getPosition()), m_c_date(other.getDate()),
    m_f_velocity(other.getVelocity()), m_f_position(other.getPosition()), m_f_date(other.getDate()), m_startDate(other.getDate())
{}

Particle::Particle(const Vec2f& start, const Vec2f& velocity) :
    m_c_velocity(velocity), m_c_position(start), m_c_date(s_absoluteTime),
    m_f_velocity(velocity), m_f_position(start), m_f_date(s_absoluteTime), m_startDate(s_absoluteTime)
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
        m_f_position=position+velocity+(s_gravity*0.5f);
        m_f_velocity=velocity+(s_gravity);
        m_f_date++;
        s_absoluteTime++;
    }
    m_c_position=m_f_position;
    m_c_velocity=m_f_velocity;
    m_c_date=m_f_date;
    return m_f_date-previousDate;
}

void Particle::validate()
{

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
    return s_absoluteTime-(m_c_date-m_startDate);
}
