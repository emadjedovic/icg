//---------------------------------------------------------------------------

#pragma hdrstop

#include "helper.h"

MySide::MySide()
{
    x1 = MyPoint(0, 0, 0);
    x2 = MyPoint(0, 0, 0);
    x3 = MyPoint(0, 0, 0);
}

MySide::MySide(MyPoint xx1, MyPoint xx2, MyPoint xx3)
{
    // first point
    x1 = MyPoint(xx1.x, xx1.y, xx1.id);
    // second point
    x2 = MyPoint(xx2.x, xx2.y, xx2.id);
    // third point
    x3 = MyPoint(xx3.x, xx3.y, xx3.id);
}

void MySide::indexes(int array[3])
{
    // passed by reference
    array[0] = x1.id;
    array[1] = x2.id;
    array[2] = x3.id;
}

void MySide::color()
{
    // using built-in TPoint class becauce of canvas->Polygon method
    TPoint tPoint[3];
    tPoint[0] = Point(x1.x, x1.y);
    tPoint[1] = Point(x2.x, x2.y);
    tPoint[2] = Point(x3.x, x3.y);

    canvas->Brush->Color =
        (TColor)RGB(50 + random(200), 50 + random(200), 50 + random(200));
    canvas->Polygon(tPoint, 2);
}

bool firstSubsetofSecond(int a[3], int b[3])
{
    set<int> bSet(b, b + 3);

    // Check if all elements of a[] exist in bSet
    for (int i = 0; i < 3; i++) {
        // If a[i] is not in bSet
        if (bSet.find(a[i]) == bSet.end())
            return false;
    }
    return true;
}

//---------------------------------------------------------------------------
#pragma package(smart_init)

