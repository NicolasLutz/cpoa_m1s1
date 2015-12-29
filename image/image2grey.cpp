#include "image2grey.h"

//====================================================================================================================================
//Constructeurs//
Image2Grey::Image2Grey() : Image2D_US<unsigned char>()
{

}

Image2Grey::Image2Grey(const Image2Grey &other) : Image2D_US<unsigned char>(other)
{

}

Image2Grey::Image2Grey(size_t width, size_t height) : Image2D_US<unsigned char>(width, height)
{

}

Image2Grey::Image2Grey(const std::string &filename) : Image2D_US<unsigned char>()
{
    load(filename);
}

//====================================================================================================================================

void Image2Grey::load(const std::string &filename)
{
    std::ifstream ifs(filename.c_str());
    if(!ifs.is_open())
        return;
    int dummy; //force le programme à fetcher seulement les nombres
    ifs.ignore(10,'\n');
    ifs >> m_width;
    ifs >> m_height;
    unsigned int format;
    ifs >> format;
    if(format==255)
    {
        size_t size=m_width*m_height;
        m_tab=new unsigned char[size];
        for(iterator_bbox it=begin(); it!=end() && ifs.good(); ++it)
        {
            ifs >> dummy;
            *it=(unsigned char)dummy;
        }
        ifs.close();
    }
}

void Image2Grey::save(const std::string &filename) const
{
    int j=0;
    std::ofstream ofs(filename.c_str());
    if(!ofs.is_open())
        return;
    ofs << "P2" << std::endl;
    ofs << m_width _spc_ m_height << std::endl;
    ofs << 255 << std::endl;
    for(Image2Grey::const_iterator_bbox it=begin();it!=end();++it)
    {
        if(j++>10) //le format accepte un maximum de 70 char/ligne, on se limitera à 10 nombres
            ofs << std::endl;
        ofs _spc_ ((int)(*it));
    }
    return;
}

void Image2Grey::clear()
{
    for(Image2Grey::iterator_bbox it=begin();it!=end();++it)
    {
        *it=0;
    }
}

//====================================================================================================================================
//Itérateurs//

Image2Grey::iterator_bbox Image2Grey::begin()
{
    iterator_bbox it(m_tab, 0, m_width-1, 0, m_width);
    return it;
}

Image2Grey::iterator_bbox Image2Grey::end()
{
    iterator_bbox it(m_tab+(m_height*m_width));
    return it;
}

Image2Grey::iterator_bbox Image2Grey::beginOf(unsigned int xStart, unsigned int xStop, unsigned int yStart)
{
    iterator_bbox it(m_tab+(yStart*m_width)+xStart, xStart, xStop, yStart, m_width);
    return it;
}

Image2Grey::iterator_bbox Image2Grey::endOf(unsigned int xStop, unsigned int yStop)
{
    iterator_bbox it(m_tab+(yStop*m_width)+xStop+1);
    return it;
}

//====================================================================================================================================
//Const Itérateur//

Image2Grey::const_iterator_bbox Image2Grey::begin() const
{
    const_iterator_bbox it(m_tab, 0, m_width-1, 0, m_width);
    return it;
}

Image2Grey::const_iterator_bbox Image2Grey::end() const
{
    const_iterator_bbox it(m_tab+(m_height*m_width));
    return it;
}

Image2Grey::const_iterator_bbox Image2Grey::beginOf(unsigned int xStart, unsigned int xStop, unsigned int yStart) const
{
    const_iterator_bbox it(m_tab+(yStart*m_width)+xStart, xStart, xStop, yStart, m_width);
    return it;
}

Image2Grey::const_iterator_bbox Image2Grey::endOf(unsigned int xStop, unsigned int yStop) const
{
    const_iterator_bbox it(m_tab+(yStop*m_width)+xStop+1);
    return it;
}

//====================================================================================================================================
//====================================================================================================================================
//Image2Grey::Itérateur//

Image2Grey::iterator_bbox::iterator_bbox(value_type* ptr):
    m_ptr(ptr)
{}

Image2Grey::iterator_bbox::iterator_bbox(value_type* ptr, unsigned int xStart, unsigned int xStop,
                                         unsigned int yStart, size_t width):
  m_ptr(ptr)
, m_xStart(xStart)
, m_xStop(xStop)
, m_spaceBetweenLines((width-m_xStop)+m_xStart)
, m_xIndex(xStart)
, m_yIndex(yStart)
{}

Image2Grey::iterator_bbox::self_type Image2Grey::iterator_bbox::operator=(const self_type& other)
{
    m_ptr = other.m_ptr;
    m_xStart=other.m_xStart;
    m_xStop=other.m_xStop;
    m_spaceBetweenLines=other.m_spaceBetweenLines;
    m_xIndex=other.m_xIndex;
    m_yIndex=other.m_yIndex;
    return *this;
}

Image2Grey::iterator_bbox::self_type Image2Grey::iterator_bbox::operator++()
{
    if(m_xIndex==m_xStop)
    {
        m_xIndex=m_xStart;
        m_ptr+=m_spaceBetweenLines;
        m_yIndex++;
    }
    else
    {
        m_xIndex++;
        m_ptr++;
    }
    return *this;
}

Image2Grey::iterator_bbox::self_type Image2Grey::iterator_bbox::operator++(int unusued)
{
    iterator_bbox i=*this;
    if(m_xIndex==m_xStop)
    {
        m_xIndex=m_xStart;
        m_ptr+=m_spaceBetweenLines;
        m_yIndex++;
    }
    else
    {
        m_xIndex++;
        m_ptr++;
    }
    return i;
}

Image2Grey::iterator_bbox::self_type Image2Grey::iterator_bbox::operator--()
{
    if(m_xIndex==m_xStart)
    {
        m_xIndex=m_xStart;
        m_ptr-=m_spaceBetweenLines;
        m_yIndex--;
    }
    else
    {
        m_xIndex--;
        m_ptr--;
    }
    return *this;
}

Image2Grey::iterator_bbox::self_type Image2Grey::iterator_bbox::operator--(int unusued)
{
    iterator_bbox i=*this;
    if(m_xIndex==m_xStart)
    {
        m_xIndex=m_xStart;
        m_ptr-=m_spaceBetweenLines;
        m_yIndex--;
    }
    else
    {
        m_xIndex--;
        m_ptr--;
    }
    return i;
}

Image2Grey::iterator_bbox::value_type& Image2Grey::iterator_bbox::operator*()
{
    return *m_ptr;
}

Image2Grey::iterator_bbox::value_type* Image2Grey::iterator_bbox::operator->()
{
    return m_ptr;
}

bool Image2Grey::iterator_bbox::operator==(const self_type& other)
{
    return m_ptr == other.m_ptr;
}

bool Image2Grey::iterator_bbox::operator!=(const self_type& other)
{
    return m_ptr != other.m_ptr;
}

Vec2f Image2Grey::iterator_bbox::Vertice()
{
    Vec2f v((float)m_xIndex, (float)m_yIndex);
    return v;
}


//====================================================================================================================================
//====================================================================================================================================
//Image2Grey::Const Itérateur//

Image2Grey::const_iterator_bbox::const_iterator_bbox(const value_type* ptr):
    m_ptr(ptr)
{}

Image2Grey::const_iterator_bbox::const_iterator_bbox(const value_type* ptr, unsigned int xStart, unsigned int xStop, unsigned int yStart, size_t width):
  m_ptr(ptr)
, m_xStart(xStart)
, m_xStop(xStop)
, m_spaceBetweenLines((width-m_xStop)+m_xStart)
, m_xIndex(xStart)
, m_yIndex(yStart)
{}

Image2Grey::const_iterator_bbox::self_type Image2Grey::const_iterator_bbox::operator=(const self_type& other)
{
    m_ptr = other.m_ptr;
    m_xStart=other.m_xStart;
    m_xStop=other.m_xStop;
    m_spaceBetweenLines=other.m_spaceBetweenLines;
    m_xIndex=other.m_xIndex;
    m_yIndex=other.m_yIndex;
    return *this;
}

Image2Grey::const_iterator_bbox::self_type Image2Grey::const_iterator_bbox::operator++()
{
    if(m_xIndex==m_xStop)
    {
        m_xIndex=m_xStart;
        m_ptr+=m_spaceBetweenLines;
        m_yIndex++;
    }
    else
    {
        m_xIndex++;
        m_ptr++;
    }
    return *this;
}

Image2Grey::const_iterator_bbox::self_type Image2Grey::const_iterator_bbox::operator++(int unusued)
{
    const_iterator_bbox i=*this;
    if(m_xIndex==m_xStop)
    {
        m_xIndex=m_xStart;
        m_ptr+=m_spaceBetweenLines;
        m_yIndex++;
    }
    else
    {
        m_xIndex++;
        m_ptr++;
    }
    return i;
}

Image2Grey::const_iterator_bbox::self_type Image2Grey::const_iterator_bbox::operator--()
{
    if(m_xIndex==m_xStart)
    {
        m_xIndex=m_xStart;
        m_ptr-=m_spaceBetweenLines;
        m_yIndex--;
    }
    else
    {
        m_xIndex--;
        m_ptr--;
    }
    return *this;
}

Image2Grey::const_iterator_bbox::self_type Image2Grey::const_iterator_bbox::operator--(int unusued)
{
    const_iterator_bbox i=*this;
    if(m_xIndex==m_xStart)
    {
        m_xIndex=m_xStart;
        m_ptr-=m_spaceBetweenLines;
        m_yIndex--;
    }
    else
    {
        m_xIndex--;
        m_ptr--;
    }
    return i;
}

const Image2Grey::const_iterator_bbox::value_type& Image2Grey::const_iterator_bbox::operator*()
{
    return *m_ptr;
}

const Image2Grey::const_iterator_bbox::value_type* Image2Grey::const_iterator_bbox::operator->()
{
    return m_ptr;
}

bool Image2Grey::const_iterator_bbox::operator==(const self_type& other)
{
    return m_ptr == other.m_ptr;
}

bool Image2Grey::const_iterator_bbox::operator!=(const self_type& other)
{
    return m_ptr != other.m_ptr;
}

Vec2f Image2Grey::const_iterator_bbox::Vertice()
{
    Vec2f v((float)m_xIndex, (float)m_yIndex);
    return v;
}

