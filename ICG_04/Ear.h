//---------------------------------------------------------------------------

#ifndef EarH
#define EarH

#include <MyPoint.h>

struct Ear
{
    MyPoint x1, x2, x3;
    Ear(MyPoint, MyPoint, MyPoint);
    Ear();
    void indexes(int array[3]);
    void color(TCanvas*);
};

//---------------------------------------------------------------------------
#endif

