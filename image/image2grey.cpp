#include "image2grey.h"

//====================================================================================================================================
//Constructeurs//
Image2Grey::Image2Grey() : Image2<unsigned char>()
{

}

Image2Grey::Image2Grey(const Image2Grey &other) : Image2<unsigned char>(other)
{

}

Image2Grey::Image2Grey(size_t width, size_t height) : Image2<unsigned char>(width, height)
{

}

Image2Grey::Image2Grey(const std::string &filename) : Image2<unsigned char>()
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
    ofs << m_width _spc_output_ m_height << std::endl;
    ofs << 255 << std::endl;
    for(Image2Grey::const_iterator_bbox it=begin();it!=end();++it)
    {
        if(j++>10) //le format accepte un maximum de 70 char/ligne, on se limitera à 10 nombres
            ofs << std::endl;
        ofs _spc_output_ ((int)(*it));
    }
    return;
}

void Image2Grey::clear()
{
    Image2Grey::iterator_bbox end=this->end();
    for(Image2Grey::iterator_bbox it=begin();it!=end;++it)
    {
        *it=0;
    }
}
