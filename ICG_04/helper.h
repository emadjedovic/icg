//---------------------------------------------------------------------------

#ifndef helperH
#define helperH

#include <set>

using namespace std;

TCanvas* canvas;

struct MyPoint
{
    double x, y;
    int id;
    MyPoint() : x(0), y(0), id(0) {};
    MyPoint(double xx, double yy, int idd) : x(xx), y(yy), id(idd) {};
};

struct MyDiagonal
{
    double x, y;
    MyDiagonal(double xx, double yy) : x(xx), y(yy) {};
    MyDiagonal() : x(0), y(0) {};
};

struct MySide
{
    MyPoint x1, x2, x3;
    MySide(MyPoint, MyPoint, MyPoint);
    MySide();
    void indexes(int array[3]);
    void color();
};

bool isSubset(int a[3], int b[3]);

//---------------------------------------------------------------------------
#endif

