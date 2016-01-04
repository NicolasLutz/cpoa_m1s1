#include "particlesystem.h"

ParticleSystem::ParticleSystem():
    m_pq(), m_set(), m_width(4096), m_height(4096)
{

}

ParticleSystem::ParticleSystem(size_t width, size_t height):
    m_pq(), m_set(), m_width(width), m_height(height)
{

}


ParticleSystem::~ParticleSystem()
{
    while(!m_pq.empty())
    {
        delete m_pq.top();
        m_pq.pop();
    }
}

const Particle* ParticleSystem::generate(const Vec2f& start)
{
    Particle* p=new Particle(start);
    m_pq.push(p);
    m_set.insert(p);
    return p;
}

bool ParticleSystem::progressOnce()
{
    if(!m_pq.empty()) //updates once per frame (this is really bad :( )
    {
        Particle *top=m_pq.top();
        m_pq.pop();
        top->update();
        //top->validate();
        const Vec2f& pos=top->getPosition();
        if(top->getDate()<1000 && pos.Y()<=m_height && pos.X()<=m_width)
            m_pq.push(top);
        else
        {
            m_set.erase(top);
            delete top;
        }
    }
    else
        return false;
    return true;
}

bool ParticleSystem::progress(int n)
{
    if(!m_pq.empty())
    {
        while(!m_pq.empty() && n>0) //update given loops (this is still bad :( )
        {
            Particle *top=m_pq.top();
            m_pq.pop();
            n-=top->update();
            //top->validate();
            const Vec2f& pos=top->getPosition();
            if(top->getDate()<1000 && pos.Y()<=m_height && pos.X()<=m_width)
                m_pq.push(top);
            else
            {
                m_set.erase(top);
                delete top;
            }
        }
    }
    else
        return false;
    return true;
}

bool ParticleSystem::progress()
{
    if(!m_pq.empty())
    {
        int n=m_pq.size();
        while(!m_pq.empty() && 0<n--) //update as many times as there are elements
        {
            Particle *top=m_pq.top();
            m_pq.pop();
            top->update();
            //top->validate();
            const Vec2f& pos=top->getPosition();
            if(top->getDate()<1000 && pos.Y()<=m_height && pos.X()<=m_width)
                m_pq.push(top);
            else
            {
                m_set.erase(top);
                delete top;
            }
        }
    }
    else
        return false;
    return true;
}

//Itérateurs//

ParticleSystem::iterator ParticleSystem::begin()
{
    return m_set.begin();
}

ParticleSystem::iterator ParticleSystem::end()
{
    return m_set.end();
}

ParticleSystem::const_iterator ParticleSystem::begin() const
{
    return m_set.begin();
}

ParticleSystem::const_iterator ParticleSystem::end() const
{
    return m_set.end();
}
