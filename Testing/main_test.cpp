#include "main_test.h"

int main(int argc, char *argv[])
{
    prettyBadTestImage2Grey();
}

void testVec2f()
{
    Vec2f v(1, 2);
    Vec2f v2(6, 5);
    std::cout << "dot v " << v << " v2 " << v2 << " = " << v*v2 << std::endl;
}

void testVec3f()
{
    Vec2f v_21(1, 2);
    Vec2f v_22(6, 5);
    Vec3f v_31=v_21^v_22;
    std::cout << "cross v " << v_21 << " v2 " << v_22 << " = " << v_31 << std::endl;
    v_31.setZ(10.0f);
    std::cout << "after we set it to 10, z value is " << v_31[2] << ", also accessible with Z()=" << v_31.Z() << std::endl;
}

void testVector()
{
    Vector<3> vec;
    vec[0]=1;
    vec[1]=2;
    vec[2]=3;
    Vector<3> vec2(vec);
    vec+=vec2;
    vec*=3;
    std::cout << vec << std::endl;
}

void testArray()
{
    Array<3,float> arr;
    Array<3,float> arr2;
    arr2[0]=3.0f;
    arr2[1]=4.0f;
    arr2[2]=5.0f;
    arr[0]=1.0f;
    arr[1]=2.0f;
    arr[2]=3.0f;
    std::cout << arr << std::endl;
    arr.exchangeWith(arr2);
    std::cout << arr << std::endl;
}

void testMatrix33f()
{
    Matrix33f mat;
    mat[0][0]=1;
    mat[0][1]=2;
    mat[0][2]=3;
    mat[1][0]=4;
    mat[1][1]=5;
    mat[1][2]=6;
    mat[2][0]=7;
    mat[2][1]=8;
    mat[2][2]=9;

    Matrix33f matCopy=mat;
    Vec3f vec3(1,-2,0.5);
    Vec3f res=mat*vec3;
    std::cout << res << std::endl; //resultat correct : http://www.anyflo.com/bret/cours/math/ma_12.jpg
    matCopy.setInvert();
    std::cout << matCopy << std::endl; //determinant nul, pas de changement
    matCopy[1].setY(10);
    matCopy.setInvert();
    std::cout << matCopy << std::endl; //http://calculis.net/matrice-invers
}

//

void testImage2D()
{
    Image2D<float> img(1,10);
    float f=0.2f;
    img.setPixel(f,0,2);
    std::cout << img.getPixel(0,2) << std::endl;
}

void prettyBadTestImage2Grey()
{
    Image2Grey img(2,2);
    img.setPixel(0,0,0);
    img.setPixel(255,1,0);
    img.setPixel(0,0,1);
    img.setPixel(255,1,1);
    img.save("testSave1.pgm");

    Image2Grey img2("testLoad.pgm");
    img2.save("testSave2.pgm");
}
