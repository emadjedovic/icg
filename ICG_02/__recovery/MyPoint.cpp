//---------------------------------------------------------------------------

#pragma hdrstop

#include "MyPoint.h"
//---------------------------------------------------------------------------

void MyPoint::Draw(TImage* Image, TColor color)
{
    Image->Canvas->Pen->Color = color;
    Image->Canvas->Ellipse(x - 3, y - 3, x + 3, y + 3);
    Image->Canvas->Brush->Color = clRed;
}

bool Criterion(MyPoint a, MyPoint b)
{
    // the left most or the highest point
    if (a.x != b.x)
        return a.x < b.x;
    else
        return a.y > b.y;
}

int Orientation(MyPoint a, MyPoint b, MyPoint c)
{
    float area =
        a.x * b.y - a.x * c.y - a.y * b.x + a.y * c.x + b.x * c.y - c.x * b.y;
    return area; // is it enough to return just the sign?
}

void DrawPointList(list<MyPoint> l, TColor color)
{
    list<MyPoint>::iterator i = l.begin();
    while (i != l.end()) {
        (*i).Draw(Image, color);
        i++;
    }
}

#pragma package(smart_init)

