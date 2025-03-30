//---------------------------------------------------------------------------

#pragma hdrstop

#include "MyPoint.h"

bool MyPoint::operator<(const MyPoint &A, const MyPoint &B)
{
    return ccw(*this, A, B) == 1 ||
           (ccw(*this, A, B) == 0 && abs(x - A.x) < abs(x - B.x));
}
bool classic(MyPoint B)
{
    return (x < B.x) || (x == B.x && y < B.y);
}

int ccw(MyPoint p0, MyPoint p1, MyPoint p2)
{
    int dx1, dx2, dy1, dy2;
    dx1 = P1.x - P0.x;
    dx2 = p2.x - p1.x;
    dy1 = p1.y - p0.y;
    dy2 = p2.y - p1.y;
    if (dx1 * dy2 > dy1 * dx2)
        return 1;
    if (dx1 * dy2 < dy1 * dx2)
        return -1;
    if ((dx1 * dx2 < 0) || (dy1 * dy2 < 0))
        return -1;
    if ((dx1 * dx1 + dy1 * dy1) < (dx2 * dx2 + dy2 * dy2))
        return 1;
    return 0;
}

//---------------------------------------------------------------------------
#pragma package(smart_init)

