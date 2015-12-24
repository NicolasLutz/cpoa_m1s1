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
    unsigned int format, count=0;
    ifs >> format;
    if(format==255)
    {
        size_t size=m_width*m_height;
        m_tab=new unsigned char[size];
        while (ifs.good() && count < size)
        {
            ifs >> dummy;
            m_tab[count++]=(unsigned char)dummy;
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
    size_t size=m_width*m_height;
    for(unsigned int i=0; i<size; i++)
    {
        if(j++>10) //le format accepte un maximum de 70 char/ligne, on se limitera à 10 nombres
            ofs << std::endl;
        ofs _spc_ ((int)m_tab[i]);
    }
}
