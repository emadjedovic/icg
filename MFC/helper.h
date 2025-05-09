#pragma once
#include <algorithm>
#include <vector>

struct MyPoint
{
    double x, y;
    MyPoint(double x, double y) : x(x), y(y) {}
    bool operator<(MyPoint);
    bool operator==(MyPoint);
    void Draw(CDC&) const;
};

int Orientation(MyPoint, MyPoint, MyPoint);

struct MySegment
{
    MyPoint A, B;

    MySegment(MyPoint a, MyPoint b) : A(a), B(b)
    {
        if (B < A)
            std::swap(A, B);
    }

    void Draw(CDC&) const;
};

std::pair<int, int> findTangents(MyPoint, std::vector<MyPoint>&);
bool PointInTriangle(MyPoint, MyPoint, MyPoint, MyPoint);
bool PointInPolygon(std::vector<MyPoint>&, MyPoint);
void DrawPolygon(CDC&, const std::vector<MyPoint>&);







