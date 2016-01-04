#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include "particle.h"
#include "_func_particle.h"
#include <ctime>
#include <queue>
#include <set>

class ParticleSystem
{
public:
    ParticleSystem();
    ParticleSystem(size_t width, size_t height);
    virtual ~ParticleSystem();

    const Particle* generate(const Vec2f& start);
    bool progressOnce(const Image2Grey& img_in, const Image2<Vec2f>& img_grad);
    bool progress(const Image2Grey& img_in, const Image2<Vec2f>& img_grad);

    //Itérateurs//

    typedef std::set<Particle *>::iterator iterator;
    typedef std::set<Particle *>::const_iterator const_iterator;

    iterator begin();
    iterator end();

    const_iterator begin() const;
    const_iterator end() const;

private:
    std::priority_queue<Particle*, std::vector<Particle*>, Func_AbsoluteDateOrder> m_pq;
    std::set<Particle *> m_set;
    size_t m_width;
    size_t m_height;
};

#endif // PARTICLESYSTEM_H
