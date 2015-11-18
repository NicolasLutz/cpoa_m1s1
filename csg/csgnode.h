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
    virtual ~CsgNode();

    //Accesseurs//
    std::string label() const;
    int id() const;
    CsgNode *parent() const;

    //Setteurs
    void setParent(CsgNode *parent);

private:
    int             m_id;
    std::string     m_label;
    CsgNode         *m_parent;
    CsgNode         *m_left;
    CsgNode         *m_right;
};

#endif // CSGNODE_H
