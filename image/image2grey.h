#ifndef IMAGE2GREY_H
#define IMAGE2GREY_H

#include <fstream>
#include "image2d_unknownsize.hpp"
#include "vec2f.h"

#define _spc_ << ' ' <<

class Image2Grey : public Image2D_US<unsigned char>
{
public:

    //Constructeurs//
    Image2Grey();

    Image2Grey(const Image2Grey &other);

    Image2Grey(size_t width, size_t height);

    Image2Grey(const std::string &filename);

    //Opérations//

    void load(const std::string &filename);

    void save(const std::string &filename) const;

    void clear();

    //Itérateurs//

    class iterator_bbox
    {
    public:
        typedef iterator_bbox self_type;
        typedef int difference_type;
        typedef unsigned char value_type;
        typedef unsigned char* pointer;
        typedef unsigned char& reference;
        typedef std::bidirectional_iterator_tag iterator_category;

        iterator_bbox() {}
        iterator_bbox(value_type* ptr);
        iterator_bbox(value_type* ptr,
                      unsigned int xStart, unsigned int xStop,
                      unsigned int yStart, size_t width);

        self_type operator=(const self_type& other);
        self_type operator++();
        self_type operator++(int unusued);
        self_type operator--();
        self_type operator--(int unusued);
        value_type& operator*();
        value_type* operator->();
        bool operator==(const self_type& other);
        bool operator!=(const self_type& other);

        //Pas dans l'interface//
        Vec2f Vertice(); ///< returns the vertice in img coordinates

    private:
        value_type*     m_ptr;
        unsigned int    m_xStart; ///< at which x are we supposed to start?
        unsigned int    m_xStop; ///< at which x is the box's edge?
        size_t          m_spaceBetweenLines; ///< used for jumping to another line
        unsigned int    m_xIndex;
        unsigned int    m_yIndex;
    };

    iterator_bbox begin();
    iterator_bbox end();

    iterator_bbox beginOf(unsigned int xStart, unsigned int xStop, unsigned int yStart);
    iterator_bbox endOf(unsigned int xStop, unsigned int yStop);

    //Const itérateur//
    class const_iterator_bbox
    {
    public:
        typedef const_iterator_bbox self_type;
        typedef int difference_type;
        typedef unsigned char value_type;
        typedef unsigned char* pointer;
        typedef unsigned char& reference;
        typedef std::bidirectional_iterator_tag iterator_category;

        const_iterator_bbox() {}
        const_iterator_bbox(const value_type* ptr);
        const_iterator_bbox(const value_type* ptr,
                      unsigned int xStart, unsigned int xStop,
                      unsigned int yStart, size_t width);

        self_type operator=(const self_type& other);
        self_type operator++();
        self_type operator++(int unusued);
        self_type operator--();
        self_type operator--(int unusued);
        const value_type& operator*();
        const value_type* operator->();
        bool operator==(const self_type& other);
        bool operator!=(const self_type& other);

        //Pas dans l'interface//
        Vec2f Vertice();

    private:
        const value_type*   m_ptr;
        unsigned int        m_xStart; ///< at which x are we supposed to start?
        unsigned int        m_xStop; ///< at which x is the box's edge?
        size_t              m_spaceBetweenLines; ///< used for jumping to another line
        unsigned int        m_xIndex;
        unsigned int        m_yIndex;
    };

    const_iterator_bbox begin() const;
    const_iterator_bbox end() const;

    const_iterator_bbox beginOf(unsigned int xStart, unsigned int xStop, unsigned int yStart) const;
    const_iterator_bbox endOf(unsigned int xStop, unsigned int yStop) const;
};

#endif // IMAGE2GREY_H
