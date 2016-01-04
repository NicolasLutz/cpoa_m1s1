#ifndef CSGREGULARPOLYGON_H
#define CSGREGULARPOLYGON_H

#include "csgprimitive.h"
#include <cmath>

#define M_2PI (2*M_PI)

class CsgRegularPolygon : public CsgPrimitive
{
public:
    CsgRegularPolygon();
    CsgRegularPolygon(const CsgRegularPolygon &other);
    CsgRegularPolygon(int nb_vertices);
    virtual ~CsgRegularPolygon();

    //Accesseurs//
    int Vertices() const;

    //Setters//
    void setVertices(int nb_vertices);

    //Opérations//
    bool intersects(const Vec2f& vertice) const;
    CsgNode *clone() const;
    void updateBB();

    //Autre//
    std::ostream& print(std::ostream &stream) const;
    std::istream& scan(std::istream &stream);


private:

    const Vec2f& _baseBB1() const;
    const Vec2f& _baseBB2() const;
    bool _leftOfClosestVertices(const Vec2f &vertice) const;
    ///true=vertice à gauche de d1 d2
    bool _leftOfd1d2(const Vec2f& vertice, const Vec2f& d1, const Vec2f& d2) const;

    static const Vec2f sc_baseBB1;
    static const Vec2f sc_baseBB2;

    int m_vertices;
    float m_precalculatedAngle; ///< Angle précalculé (radians)
};

#endif // CSGREGULARPOLYGON_H
