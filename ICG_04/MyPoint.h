//---------------------------------------------------------------------------

#ifndef MyPointH
#define MyPointH

struct MyPoint
{
    double x, y;
    MyPoint() : x(0), y(0) {}
    MyPoint(double xx, double yy) : x(xx), y(yy) {}
    bool operator<(const MyPoint &, const MyPoint &);
    bool classic(MyPoint B);
};

int ccw(MyPoint, MyPoint, MyPoint);

//---------------------------------------------------------------------------
#endif

