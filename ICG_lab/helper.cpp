//---------------------------------------------------------------------------

#pragma hdrstop

#include "helper.h"

bool MyPoint::operator<(MyPoint p)
{
    if (x < p.x)
        return true;
    if (x > p.x)
        return false;
    return y < p.y; // Compare y if x values are equal
}

void MyPoint::Draw(TImage* Image, TColor color, int size)
{
	Image->Canvas->Brush->Color = color;
    Image->Canvas->Ellipse(x - size, y - size, x + size, y + size);
    Image->Canvas->Brush->Color = clBlack; // Reset brush color
}

// Returns -1 (left turn), 1 (right turn), or 0 (collinear)
int Orientation(MyPoint A, MyPoint B, MyPoint C)
{
    double x1 = A.x;
    double x2 = B.x;
    double x3 = C.x;

    double y1 = A.y;
    double y2 = B.y;
    double y3 = C.y;

    double area = x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2);
    if (area > 0)
        return -1;
    if (area < 0)
        return 1;
    return 0;
}
//---------------------------------------------------------------------------
#pragma package(smart_init)

