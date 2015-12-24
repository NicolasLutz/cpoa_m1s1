#ifndef IMAGE2GREY_H
#define IMAGE2GREY_H

#include "image2d_unknownsize.hpp"
#include <fstream>

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

};

#endif // IMAGE2GREY_H
