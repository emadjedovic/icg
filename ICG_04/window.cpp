//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Window.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TTriangulation* Triangulation;
Graphics::TBitmap* bmp = new Graphics::TBitmap;

// The area is positive if a,b,c are oriented ccw,
// negative if cw, and zero if the points are collinear.
int Area2(const MyPoint &a, const MyPoint &b, const MyPoint &c)
{
    return (a.x * b.y - b.x * a.y) + (b.x * c.y - c.x * b.y) +
           (c.x * a.y - a.x * c.y);
}

// Returns twice the area of the polygon.
int AreaPoly2(int n, const MyPoint poly[100])
{
    int sum(0);

    // It breaks the n-sided polygon into
    // (n - 2) triangles, all sharing the first vertex.
    for (int i = 1; i < n - 1; i++)
        sum += Area2(poly[0], poly[i], poly[i + 1]);

    return sum;
}

bool XOR(bool x, bool y)
{
    !x ^ !y;
}

/*
	Returns true iff ab properly intersects cd: they share
	a point interior to both segments.  The properness of the
	intersection is ensured by using strict leftness.
*/
bool IntersectProp(
    const MyPoint &a, const MyPoint &b, const MyPoint &c, const MyPoint &d)
{
    return XOR(Left(a, b, c), Left(a, b, d)) &&
           XOR(Left(c, d, a), Left(c, d, b))
}

/*
	Returns true iff c is strictly to the left of the directed
	line through a to b.
*/
bool Left(const MyPoint &a, const MyPoint &b, const MyPoint &c)
{
    return Area2(a, b, c) > 0;
}

bool LeftOn(const MyPoint &a, const MyPoint &b, const MyPoint &c)
{
    return Area2(a, b, c) >= 0;
}

bool Collinear(const MyPoint &a, const MyPoint &b, const MyPoint &c)
{
    return Area2(a, b, c) == 0;
}

// puts a-b into c
void SubtractVectors(const MyPoint &a, const MyPoint &b, MyPoint &c)
{
    c.x = a.x - b.x;
    c.y = a.y - b.y;
}

// vector originating from the origin (0, 0)
int Dot(const MyPoint &a, const MyPoint &b)
{
    return a.x * b.x + a.y * b.y;
}

// Returns the square of the length of the vector p.
int Length2(const MyPoint &p)
{
    return Dot(p, p);
}

bool IsPointOnSegment(const MyPoint &a, const MyPoint &b, const MyPoint &c)
{
    MyPoint vector_ab, vector_ac;

    // Check if points a, b, and c are collinear (lie on the same line)
    if (!Collinear(a, b, c))
        return false;

    // Calculate vector from a to b (ab)
    SubtractVectors(b, a, vector_ab);

    // Calculate vector from a to c (ac)
    SubtractVectors(c, a, vector_ac);

    // Check if point c lies in the same direction as b from a
    // and if c's distance from a is less than or equal to b's distance from a
    return Dot(vector_ac, vector_ab) >= 0 &&
           Length2(vector_ac) <= Length2(vector_ab);
}

bool Intersect(MyPoint a, MyPoint b, MyPoint c, MyPoint d) {}

bool Diagonalie(int i, int j, int n, MyPoint P[100]) {}

bool Diagonal(int i, int j, int n, MyPoint P[100]) {}

void PointAssign(MyPoint* a, MyPoint* b) {}

bool InCone(int i, int j, int n, MyPoint P[100]) {}

void ClipEar(int i, int n, MyPoint P[100]) {}

//---------------------------------------------------------------------------
__fastcall TTriangulation::TTriangulation(TComponent* Owner) : TForm(Owner) {}
//---------------------------------------------------------------------------
void __fastcall TTriangulation::ImageMouseDown(
    TObject* Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    return;
}
//---------------------------------------------------------------------------

void __fastcall TTriangulation::ButtonTriangulationClick(TObject* Sender)
{
    return;
}
//---------------------------------------------------------------------------

void __fastcall TTriangulation::ButtonClearClick(TObject* Sender)
{
    canvas->Brush->Color = clWhite;
    canvas->FillRect(Image->ClientRect);
    numPoints = 0;
    numSides = 0;
    numDiagonals = 0;
}
//---------------------------------------------------------------------------

void __fastcall TTriangulation::ButtonImproveClick(TObject* Sender)
{
    return;
}
//---------------------------------------------------------------------------

void __fastcall TTriangulation::FormCreate(TObject* Sender)
{
    canvas = Image->Canvas;
    canvas->Brush->Color = clWhite;
    canvas->FillRect(Image->ClientRect);
    numPoints = 0;
}
//---------------------------------------------------------------------------

