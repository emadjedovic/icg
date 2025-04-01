//---------------------------------------------------------------------------

#pragma hdrstop

#include "helper.h"

void MyPoint::Draw(TImage* Image, TColor color, int size)
{
    Image->Canvas->Brush->Color = color;
    Image->Canvas->Ellipse(x - size, y - size, x + size, y + size);
    Image->Canvas->Brush->Color = clBlack; // Reset brush color
}

bool MyPoint::operator<(MyPoint p)
{
    if (x < p.x)
        return true;
    if (x > p.x)
        return false;
    return y < p.y; // Compare y if x values are equal
}

bool MyPoint::operator==(MyPoint p)
{
    return x == p.x && y == p.y;
}

void MySegment::Draw(TImage* Image, TColor color, int size)
{
    Image->Canvas->Brush->Color = color;
    Image->Canvas->Pen->Color = color;

    A.Draw(Image, color, size);
    B.Draw(Image, color, size);

    Image->Canvas->MoveTo(A.x, A.y);
    Image->Canvas->LineTo(B.x, B.y);

    Image->Canvas->Brush->Color = clBlack;
    Image->Canvas->Pen->Color = clBlack;
}

void DrawPolygon(TImage* Image, const vector<MyPoint> &points, TColor color)
{
    int numPoints = points.size();
    if (numPoints == 0)
        return;

    // Iterate through all points and draw edges
    for (int i = 0; i < numPoints; i++) {
        size_t nextIndex = (i + 1) % numPoints; // Ensures the polygon is closed
        MyPoint currentPoint = points[i];
        MyPoint nextPoint = points[nextIndex];

        MySegment edge(currentPoint, nextPoint);
        edge.Draw(Image, color);
        currentPoint.Draw(Image, color);
    }

    // Explicitly draw the first point again to ensure closure
    MyPoint firstPoint = points[0];
    firstPoint.Draw(Image, color);
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

    // actually modified, + area means positive orientation but due to
    // TECHNICALITIES we do the opposite...
    if (area > 0)
        return -1;
    if (area < 0)
        return 1;
    return 0;
}

bool PointInTriangle(MyPoint A, MyPoint B, MyPoint C, MyPoint P)
{
    int o1 = Orientation(A, B, P);
    int o2 = Orientation(B, C, P);
    int o3 = Orientation(C, A, P);

    return o1 == o2 && o2 == o3;
}

bool PointInPolygon(vector<MyPoint> &convPoly, MyPoint P)
{
    if (convPoly.size() < 3)
        return false;

    MyPoint firstPoint(convPoly[0]);

    int startIndex = 1;
    int endIndex = convPoly.size() - 1;

    while (endIndex - startIndex > 1) {
        int middleIndex = (startIndex + endIndex) / 2;
        if (Orientation(firstPoint, convPoly[middleIndex], P) > 0)
            endIndex = middleIndex;
        else
            startIndex = middleIndex;
    }

    return PointInTriangle(
        firstPoint, convPoly[startIndex], convPoly[endIndex], P);
}

//---------------------------------------------------------------------------
#pragma package(smart_init)

