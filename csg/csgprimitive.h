#ifndef CSGPRIMITIVE_H
#define CSGPRIMITIVE_H

#include "csgnode.h"
#include "matrix33f.h"

class CsgPrimitive : public CsgNode
{
public:
    //Constructeurs//
    CsgPrimitive();
    CsgPrimitive(const CsgPrimitive &other);
    virtual ~CsgPrimitive();

    //Accesseurs//
    const Vec2f& Origin() const;

    //Opérations//
    virtual bool intersects(const Vec2f& other) const=0;

    //Transformations//
    const Matrix33f& T_Matrix() const;      ///< gets the current matrix
    const Matrix33f& T_Inverted() const;    ///< gets the inverted matrix
    const Matrix33f& T_Saved() const;       ///< gets the saved matrix

    void T_save();                          ///< saves the current matrix
    void T_reset();                         ///< sets current matrix to saved
    void T_nullify();                       ///< sets current matrix to default

    void T_set(const Matrix33f &transfo);   ///< sets the current matrix

private:
    Matrix33f m_T_matrix;
    Matrix33f m_T_inverted;
    Matrix33f m_T_saved;
    static const Vec2f sc_origin;
};

#endif // CSGPRIMITIVE_H
