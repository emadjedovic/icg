//---------------------------------------------------------------------------

#ifndef MyPointH
#define MyPointH
#include <list>
using namespace std;
//---------------------------------------------------------------------------

struct MyPoint
{
    float x, y;
    MyPoint() : x(0), y(0) {};
    MyPoint(float x, float y) : x(x), y(y) {};
    void Draw(TImage*, TColor = clWhite);
};

bool Criterion(MyPoint, MyPoint);
int Orientation(MyPoint, MyPoint, MyPoint);
void DrawPointList(TImage*, list<MyPoint>, TColor);

#endif
