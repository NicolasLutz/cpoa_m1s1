#ifndef PARTICLE_H
#define PARTICLE_H

#include "vec2f.h"
#include <ctime>

class Particle
{
public:
    Particle();
    Particle(const Particle &other);
    Particle(const Vec2f& start, const Vec2f& velocity=Vec2f(0,0));

    int update();
    void validate();

    //Accesseurs//

    const Vec2f& getVelocity() const;
    const Vec2f& getPosition() const;
    int getDate() const;
    int getPriority() const;

private:

    Vec2f m_start;

    Vec2f m_c_velocity;
    Vec2f m_c_position; ///< c stands for current
    int m_c_date; ///< in ms

    Vec2f m_f_velocity;
    Vec2f m_f_position; ///<f stands for future
    int m_f_date;

    int m_startDate;

    static Vec2f s_gravity;
    static int s_absoluteTime;
};

#endif // PARTICLE_H
