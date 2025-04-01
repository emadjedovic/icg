//---------------------------------------------------------------------------

#ifndef helperH
#define helperH

#include <algorithm>
#include <vector>

using namespace std;

struct MyPoint
{
    double x, y;
    MyPoint(double x, double y) : x(x), y(y) {}
    bool operator<(MyPoint);
    bool operator==(MyPoint);
    void Draw(TImage*, TColor = clBlack, int = 3);
};

int Orientation(MyPoint, MyPoint, MyPoint);

struct MySegment
{
    MyPoint A, B;
    MySegment(MyPoint A, MyPoint B) : A(A), B(B)
    {
        if (B < A)
            swap(A, B);
    }
    void Draw(TImage*, TColor = clBlack, int = 3);
};

void DrawPolygon(TImage*, const vector<MyPoint> &, TColor = clBlue);
bool PointInTriangle(MyPoint, MyPoint, MyPoint, MyPoint);
bool PointInPolygon(vector<MyPoint> &, MyPoint);

//---------------------------------------------------------------------------
#endif

