//---------------------------------------------------------------------------

#pragma hdrstop

#include "MyPoint.h"


bool comparePoints(MyPoint A, MyPoint B)
{
    return (A.x < B.x) || (A.x == B.x && A.y < B.y);
}

int ccw(MyPoint p0, MyPoint p1, MyPoint p2)
{
    int dx1, dx2, dy1, dy2;
    dx1 = p1.x - p0.x;
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

