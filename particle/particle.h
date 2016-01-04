#ifndef PARTICLE_H
#define PARTICLE_H

#include "matrix33f.h"
#include "image2grey.h"
#include "imgGradient.h"
#include <ctime>

class Particle
{
public:
    Particle();
    Particle(const Particle &other);
    Particle(const Vec2f& start, const Vec2f& velocity=Vec2f(0,0));

    int update();
    void validate(const Image2Grey& img_in, const Image2<Vec2f> &img_grad);

    //Accesseurs//

    const Vec2f& getVelocity() const;
    const Vec2f& getPosition() const;
    int getDate() const;
    int getPriority() const;

    //Setters//

    static void addAbsoluteTime();

private:

    void _giveCollisionPoint(const Image2Grey& img_in, int &x, int &y);

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
    static Matrix33f s_toTan;
    static Matrix33f s_toCounterTan;
};

#endif // PARTICLE_H
