//---------------------------------------------------------------------------

#ifndef MyPointH
#define MyPointH

bool XOR(bool x, bool y);

struct MyPoint
{
    double x, y;
    int id;
    MyPoint() : x(0), y(0), id(0) {};
    MyPoint(double xx, double yy, int idd) : x(xx), y(yy), id(idd) {};
    MyPoint &operator=(const MyPoint &);
    MyPoint operator-(const MyPoint &b) const;
    int Dot(const MyPoint &b) const;
    int Length2() const;
    bool IsPointOnSegment(const MyPoint &a, const MyPoint &b) const;
};

int Area2(const MyPoint &, const MyPoint &, const MyPoint &);
bool IntersectProp(
    const MyPoint &, const MyPoint &, const MyPoint &, const MyPoint &);
bool Left(const MyPoint &, const MyPoint &, const MyPoint &);
bool LeftOn(const MyPoint &, const MyPoint &, const MyPoint &);
bool Collinear(const MyPoint &, const MyPoint &, const MyPoint &);
bool Intersect(
    const MyPoint &, const MyPoint &, const MyPoint &, const MyPoint &);

//---------------------------------------------------------------------------
#endif

