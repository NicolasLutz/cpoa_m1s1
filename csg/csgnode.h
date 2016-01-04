#ifndef CSGNODE_H
#define CSGNODE_H

#include <string>
#include <iostream>
#include "matrix33f.h"
#include "boundingbox.h"

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
    const unsigned int& Id() const;
    const std::string& Label() const;
    CsgNode *Parent() const;
    const BoundingBox& BBox() const;

    //Setteurs//
    void setParent(CsgNode *parent);
    void setLabel(const std::string &label);

    //Statique//
    static void resetCounter();
    static unsigned int Counter();

    //Opérations//
    virtual bool intersects(const Vec2f &vertice) const=0;
    virtual bool intersectsBBox(const Vec2f &vertice) const=0;
    virtual CsgNode *clone() const=0;
    virtual void updateBB()=0;

    //Autres//
    virtual std::ostream& print(std::ostream &stream) const=0;
    virtual std::istream& scan(std::istream &stream)=0;
    friend std::ostream& operator<< (std::ostream &stream, const CsgNode &object);
    friend std::istream& operator>> (std::istream &stream, CsgNode &object);

private:

    static unsigned int s_count;
    unsigned int    m_id;
    std::string     m_label;

protected:
    CsgNode         *m_parent;
    BoundingBox     m_BB;
};

#endif // CSGNODE_H
