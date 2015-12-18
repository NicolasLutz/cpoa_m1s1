#ifndef CSGNODE_H
#define CSGNODE_H

#include <string>
#include <iostream>

#define _e_ 0.005 //define a floating point allowed error

class CsgNode
{
public:
    //Constructeurs//
    CsgNode();
    CsgNode(const CsgNode &other);
    CsgNode(const std::string &label, CsgNode *left=NULL, CsgNode *right=NULL);
    virtual ~CsgNode();

    //Accesseurs//
    const std::string& Label() const;
    const unsigned int& Id() const;

    //CsgNode *Parent() const;
    CsgNode *Left() const;
    CsgNode *Right() const;

    //Setteurs
    void setLeft(CsgNode *left);
    void setRight(CsgNode *right);
    void setLabel(const std::string &label);
    //void setParent(CsgNode *parent);

    //Transformations//
    virtual void T_reset()=0;
    virtual void T_rotate(float rad)=0;
    virtual void T_translate(float tx, float ty)=0;
    virtual void T_scale(float vx, float vy)=0;

private:
    static unsigned int s_count;
    unsigned int    m_id;
    std::string     m_label;
    CsgNode         *m_left;
    CsgNode         *m_right;
    //CsgNode         *m_parent; TODO
};

#endif // CSGNODE_H
