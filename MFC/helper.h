#pragma once
#include <algorithm>
#include <vector>
#include <list>
#include <iterator>
#include <queue>
#include <set>

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
    bool horizontal() const { return A.y == B.y; };
    bool vertical() const { return A.x == B.x; };
};

std::pair<int, int> findTangents(MyPoint, std::vector<MyPoint>&);
bool PointInTriangle(MyPoint, MyPoint, MyPoint, MyPoint);
bool PointInPolygon(std::vector<MyPoint>&, MyPoint);
void DrawPolygon(CDC&, const std::vector<MyPoint>&);

double distance (MyPoint, MyPoint);

std::list<int>::iterator moveIteratorForward(std::list<int>::iterator, std::list<int>&);
std::list<int>::iterator moveIteratorBackward(std::list<int>::iterator, std::list<int>&);

// intersection of horizontal and vertical segments

struct HorVerSegmentsY {
    /*
    process events from left to right along the x-axis
    */
    bool operator()(std::pair<MyPoint, MySegment*> e1, std::pair<MyPoint, MySegment*> e2) {
        return e1.first.x > e2.first.x;
    }
};


struct HorSegmentsY {
     /*
    sorts horizontal segments from top to bottom (y ascending),
    and from left to right (x ascending
    */
    bool operator()(MySegment* d1, MySegment* d2) const {
        if (d1->A.y == d2->A.y) {
            return d1->A.x < d2->A.x;
        }
        return d1->A.y < d2->A.y;
    }
};








