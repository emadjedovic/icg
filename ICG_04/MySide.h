//---------------------------------------------------------------------------

#ifndef MySideH
#define MySideH

#include <MyPoint.h>

struct MySide
{
    MyPoint x1, x2, x3;
    MySide(MyPoint, MyPoint, MyPoint);
    MySide();
    void indexes(int array[3]);
    void color(TCanvas*);
};

//---------------------------------------------------------------------------
#endif

