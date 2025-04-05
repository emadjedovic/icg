//---------------------------------------------------------------------------

#ifndef MyEarH
#define MyEarH

#include <MyPoint.h>

struct MyEar
{
    MyPoint x1, x2, x3;
    MyEar(MyPoint, MyPoint, MyPoint);
    MyEar();
    void indexes(int array[3]);
    void color(TCanvas*);
};

//---------------------------------------------------------------------------
#endif

