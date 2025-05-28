#pragma once

#include <algorithm>
#include <vector>
#include <list>
#include <iterator>
#include <queue>
#include <set>

using namespace std;

struct MyPoint
{
    double x, y;
    MyPoint(double x=0, double y=0) : x(x), y(y) {}
    bool operator<(MyPoint);
    bool operator==(MyPoint);
    void Draw(CDC& dc, COLORREF color = RGB(0, 0, 0), int radius = 3) const;
};

int Orientation(MyPoint, MyPoint, MyPoint);

struct MySegment
{
    MyPoint A, B;

    MySegment(MyPoint a, MyPoint b) : A(a), B(b)
    {
        if (B < A)
            swap(A, B);
    }

    void Draw(CDC&, COLORREF color = RGB(0, 0, 0), int thickness=1) const;
    bool horizontal() const { return A.y == B.y; };
    bool vertical() const { return A.x == B.x; };
};

pair<int, int> findTangents(MyPoint, vector<MyPoint>&);
bool PointInTriangle(MyPoint, MyPoint, MyPoint, MyPoint);
bool PointInPolygon(vector<MyPoint>&, MyPoint);
void DrawPolygon(CDC&, const vector<MyPoint>&,COLORREF color = RGB(0, 0, 0), int thickness=1);
double distance (MyPoint, MyPoint);

list<int>::iterator moveIteratorForward(list<int>::iterator, list<int>&);
list<int>::iterator moveIteratorBackward(list<int>::iterator, list<int>&);

// intersection of horizontal and vertical segments

struct HorVerSegmentsX {
    /*
    process events from left to right along the x-axis
    */
    bool operator()(pair<MyPoint, MySegment*> e1, pair<MyPoint, MySegment*> e2) {
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

struct EventsX {
    bool operator() (pair<MyPoint, pair<MySegment*, MySegment*>> e1, pair<MyPoint, pair<MySegment*, MySegment*>> e2) {
        return e1.first.x > e2.first.x;
    }
};

struct ActiveSegmentsTree {
    bool operator()(MySegment* s1, MySegment* s2) const {
        MyPoint A = s1->A;
        MyPoint B = s1->B;
        MyPoint C = s2->A;
        MyPoint D = s2->B;

        if (A == C) {
            return Orientation(A, B, D) < 0;
        }
        if (A < C) {
            return Orientation(A, B, C) < 0;
        }
        else {
            return Orientation(C, D, A) > 0;
        }
    }
};

bool doSegmentsIntersect(MySegment, MySegment);
MyPoint getIntersectionPoint(MySegment, MySegment);

void handleIntersection(int x_sweep_line, MySegment* seg1, MySegment* seg2,
    set<MySegment*, ActiveSegmentsTree>& activeSegments, vector<MyPoint>& intersections,
    priority_queue<pair<MyPoint, pair<MySegment*, MySegment*>>, vector<pair<MyPoint, pair<MySegment*, MySegment*>>>, EventsX>& events);

// KD-Tree

enum NodeType { HORIZONTAL, VERTICAL, LEAF };
enum IntersectionType { EMPTY, FULL, PARTIAL };

struct MyRectangle {
    int xmin, xmax, ymin, ymax;
    MyRectangle(int xmin, int xmax, int ymin, int ymax) : xmin(xmin), xmax(xmax), ymin(ymin), ymax(ymax) {}
    void Draw(CDC&, COLORREF color = RGB(0, 0, 0), int thickness = 3) const;
};

IntersectionType rectanglesIntersection(MyRectangle, MyRectangle);
bool isPointInsideRectangle(MyPoint, MyRectangle);

class KDNode {
    KDNode* parentNode;
    KDNode* leftNode, *rightNode;
    NodeType nodeType;
    MyRectangle region;
    MyPoint pt;
    friend class KDTree;
public:
    KDNode(KDNode* parentNode, NodeType nodeType, MyRectangle region, KDNode* leftNode, KDNode* rightNode, MyPoint pt) : parentNode(parentNode), leftNode(leftNode), rightNode(rightNode), nodeType(nodeType), pt(pt), region(region) {}
};

class KDTree {
    KDNode* rootNode;
    KDNode* constructTree(KDNode*, vector<MyPoint>&, bool);
    void drawLine(CDC&, KDNode*) const;
    void addLeaves(KDNode*, vector<MyPoint>&);
public:
    KDTree(vector<MyPoint>&, int, int);
    void Draw(CDC&, KDNode* = nullptr, bool = true) const;
    void query(MyRectangle, vector<MyPoint>&, KDNode* = nullptr, bool = true);
};