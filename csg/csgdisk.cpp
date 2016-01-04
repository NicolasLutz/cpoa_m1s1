#include "csgdisk.h"

const Vec2f CsgDisk::sc_baseBB1(-0.5f,-0.5f);
const Vec2f CsgDisk::sc_baseBB2(0.5f, 0.5f);

CsgDisk::CsgDisk() : CsgPrimitive()
{
    m_BB.setXY1(_baseBB1());
    m_BB.setXY2(_baseBB2());
}

//----------------------------------------------------------------------------

CsgDisk::CsgDisk(const CsgDisk &other) : CsgPrimitive(other)
{}

//----------------------------------------------------------------------------

CsgDisk::~CsgDisk()
{}

//----------------------------------------------------------------------------
//Opérations//

bool CsgDisk::intersects(const Vec2f &vertice) const
{
    if(!intersectsBBox(vertice))
        return false;
    Vec2f transformedVertice = T_Inverted() * vertice;
    return transformedVertice.distance(Origin()) <= 0.5f;
}

CsgNode* CsgDisk::clone() const
{
    return new CsgDisk(*this);
}

//----------------------------------------------------------------------------
//Autre//

std::ostream& CsgDisk::print(std::ostream &stream) const
{
    stream << 'D' _spc_output_
              /*'\"' << object.Label() << '\"' _spc_output_*/
              T_Matrix() << std::endl;
    return stream;
}

std::istream& CsgDisk::scan(std::istream &stream)
{
    Matrix33f m;
    stream >> m;
    T_set(m);
    return stream;
}

//----------------------------------------------------------------------------
//Transformations//

void CsgDisk::T_applyTransfo(float tx, float ty, float rad, float vx, float vy)
{
    m_T_matrix.setId();
    m_T_matrix.addTranslation(tx, ty);
    m_T_matrix.addScaling(vx, vy);
    //m_T_matrix.addRotation(rad); ignoré: un cercle n'a pas de rotation...
    m_T_inverted=m_T_matrix.invert();
    updateBB();
}

//----------------------------------------------------------------------------
//Private//

const Vec2f& CsgDisk::_baseBB1() const
{
    return sc_baseBB1;
}

const Vec2f& CsgDisk::_baseBB2() const
{
    return sc_baseBB2;
}
