#include "csgregularpolygon.h"

const Vec2f CsgRegularPolygon::sc_baseBB1(-0.5f, -0.5f);
const Vec2f CsgRegularPolygon::sc_baseBB2(0.5f, 0.5f);

CsgRegularPolygon::CsgRegularPolygon() :
    CsgPrimitive(), m_vertices(3)
{
    m_BB.setXY1(_baseBB1());
    m_BB.setXY2(_baseBB2());
}

//----------------------------------------------------------------------------

CsgRegularPolygon::CsgRegularPolygon(const CsgRegularPolygon &other) :
    CsgPrimitive(other), m_vertices(other.Vertices()), m_precalculatedAngle((2*M_PI)/m_vertices)
{}

//----------------------------------------------------------------------------

CsgRegularPolygon::CsgRegularPolygon(int nb_vertices) :
    CsgPrimitive(), m_vertices(nb_vertices), m_precalculatedAngle((2*M_PI)/m_vertices)
{
    m_BB.setXY1(_baseBB1());
    m_BB.setXY2(_baseBB2());
}

//----------------------------------------------------------------------------

CsgRegularPolygon::~CsgRegularPolygon()
{}

//----------------------------------------------------------------------------
//Accesseurs//

int CsgRegularPolygon::Vertices() const
{
    return m_vertices;
}

//----------------------------------------------------------------------------
//Setters//
void CsgRegularPolygon::setVertices(int nb_vertices)
{
    m_vertices=nb_vertices;
    m_precalculatedAngle=(2*M_PI)/m_vertices;
}

//----------------------------------------------------------------------------
//Opérations//

bool CsgRegularPolygon::intersects(const Vec2f &vertice) const
{
    if(!intersectsBBox(vertice))
        return false;
    Vec2f transformedVertice = T_Inverted() * vertice;
    return transformedVertice.distance(Origin()) <= 0.5f && _leftOfClosestVertices(transformedVertice);
}

CsgNode* CsgRegularPolygon::clone() const
{
    return new CsgRegularPolygon(*this);
}

void CsgRegularPolygon::updateBB()
{
    Matrix33f noRotateBB;
    noRotateBB.addScaling(m_T_matrix.Vx(), m_T_matrix.Vy());
    noRotateBB.addTranslation(m_T_matrix.Tx(), m_T_matrix.Ty());
    m_BB.applyTransfo(noRotateBB, _baseBB1(), _baseBB2());
    if(m_parent!=NULL)
        m_parent->updateBB();
}

//----------------------------------------------------------------------------
//Private//

bool CsgRegularPolygon::_leftOfClosestVertices(const Vec2f &vertice) const
{
    /*première partie: déterminer les points du polygone les plus proches*/

    //angle jusqu'à vertice
    float angleToVertice=std::atan2(vertice.Y(), vertice.X());

    //dans quelle portion du polygone se situe notre point ?
    float portionOfPolygon=angleToVertice/m_precalculatedAngle;
    float closestAngle1=std::floor(portionOfPolygon)*m_precalculatedAngle;
    float closestAngle2=std::ceil(portionOfPolygon)*m_precalculatedAngle;

    //à quels points cela correspond ? (Calcul en live des points concernés)

    Vec2f d1,d2;

    d1.setX(std::cos(closestAngle1)*0.5f);
    d1.setY(std::sin(closestAngle1)*0.5f);

    d2.setX(std::cos(closestAngle2)*0.5f);
    d2.setY(std::sin(closestAngle2)*0.5f);

    //est-ce que notre point est à gauche de d1d2 ?
    return _leftOfd1d2(vertice, d1, d2);
}

bool CsgRegularPolygon::_leftOfd1d2(const Vec2f& vertice, const Vec2f& d1, const Vec2f& d2) const
{
    /*second partie: méthode du déterminant*/
    return ( (d2.X()-d1.X())*(vertice.Y()-d1.Y()) - (d2.Y()-d1.Y())*(vertice.X()-d1.X()) ) > 0;
}

std::ostream& CsgRegularPolygon::print(std::ostream &stream) const
{
    stream << 'R' _spc_output_
              /*'\"' << object.Label() << '\"' _spc_output_*/
              Vertices() _spc_output_
              T_Matrix() << std::endl;
    return stream;
}

std::istream& CsgRegularPolygon::scan(std::istream &stream)
{
    int vertices;
    Matrix33f m;
    stream >> vertices >> m;
    setVertices(vertices);
    T_set(m);
    return stream;
}

const Vec2f& CsgRegularPolygon::_baseBB1() const
{
    return sc_baseBB1;
}

const Vec2f& CsgRegularPolygon::_baseBB2() const
{
    return sc_baseBB2;
}
