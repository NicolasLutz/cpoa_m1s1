#ifndef CSGNODE_H
#define CSGNODE_H

#include <string>
#include <iostream>
#include "matrix33f.h"

#define _e_ 0.005 //define a floating point allowed error

class CsgNode
{
public:
    //Constructeurs//
    CsgNode();
    CsgNode(const CsgNode &other);
    CsgNode(const std::string &label);
    virtual ~CsgNode();

    //Accesseurs//
    const std::string& Label() const;
    const unsigned int& Id() const;
    const Matrix33f& T_Matrix() const;

    CsgNode *Parent() const;

    //Setteurs
    void setParent(CsgNode *parent);
    void setLabel(const std::string &label);

    //Opérations//
    virtual bool intersects(const Vec2f &vertice) const=0;
    //virtual bool intersectsBBox(const Vec2f &vertice) const=0;

private:
    static unsigned int s_count;
    unsigned int    m_id;
    std::string     m_label;
    CsgNode         *m_parent;
};

#endif // CSGNODE_H
