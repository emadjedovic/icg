#include "pch.h"
#include "helper.h"

bool MyPoint::operator<(MyPoint p)
{
    if (x < p.x)
        return true;
    if (x > p.x)
        return false;
    return y < p.y;
}

bool MyPoint::operator==(MyPoint p)
{
    return x == p.x && y == p.y;
}

//void MyPoint::Draw(CDC& dc) const
//{
//    dc.Ellipse(x - 3, y - 3, x + 3, y + 3);
//}

void MyPoint::Draw(CDC& dc, COLORREF color, int radius) const
{
    CPen pen(PS_SOLID, 1, color);
    CBrush brush(color);

    CPen* oldPen = dc.SelectObject(&pen);
    CBrush* oldBrush = dc.SelectObject(&brush);

    dc.Ellipse(x - radius, y - radius, x + radius, y + radius);

    dc.SelectObject(oldPen);
    dc.SelectObject(oldBrush);
}


//  -1 (left turn), 1 (right turn), 0 (collinear)
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

bool PointInTriangle(MyPoint A, MyPoint B, MyPoint C, MyPoint P)
{
    int o1 = Orientation(A, B, P);
    int o2 = Orientation(B, C, P);
    int o3 = Orientation(C, A, P);

    return o1 == o2 && o2 == o3;
}

bool PointInPolygon(vector<MyPoint>& convPoly, MyPoint P)
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
// assuming ccw point enumeration
bool isLeftTangent(MyPoint T, MyPoint S, MyPoint prev, MyPoint next)
{
    // both neighbours underneath
    return Orientation(T, S, prev) < 0 && Orientation(T, S, next) < 0;
}

bool isRightTangent(MyPoint T, MyPoint S, MyPoint prev, MyPoint next)
{
    // both neighbours above
    return Orientation(T, S, prev) > 0 && Orientation(T, S, next) > 0;
}

bool middlePointOnGreaterArc(MyPoint T, MyPoint S, MyPoint next)
{
    return Orientation(T, S, next) < 0;
}

pair<int, int> findTangents(MyPoint T, vector<MyPoint>& conv)
{
    int n = conv.size();
    int left_i = -1;
    int right_i = -1;
    int start = 0;
    int end = n - 1;

    // left tangent

    while (end - start > 1) {
        int middle_i = (start + end) / 2;
        int prev_i = (middle_i + n - 1) % n;
        int next_i = (middle_i + 1) % n;

        MyPoint prev = conv[prev_i];
        MyPoint next = conv[next_i];
        MyPoint middle = conv[middle_i];

        if (isLeftTangent(T, middle, prev, next)) {
            left_i = middle_i;
            break;
        }

        if (middlePointOnGreaterArc(T, middle, next)) {
            if (Orientation(T, middle, conv[start]) > 0 &&
                Orientation(T, conv[start], conv[(start + n - 1) % n]) > 0)
            {
                // first case
                start = middle_i;
            }
            else {
                // second case
                end = middle_i;
            }
        }
        else {
            // smaller arc
            if (Orientation(T, middle, conv[start]) > 0 &&
                Orientation(T, conv[start], conv[(start + n - 1) % n]) < 0)
            {
                // first case
                end = middle_i;
            }
            else {
                // second case
                start = middle_i;
            }
        }
    }

    if (left_i == -1) {
        MyPoint before_start = conv[(start + n - 1) % n];
        MyPoint after_start = conv[(start + 1) % n];
        if (isLeftTangent(T, conv[start], before_start, after_start)) {
            left_i = start;
        }
        else {
            left_i = end;
        }
    }

    start = 0;
    end = n - 1;

    // right tangent

    while (end - start > 1) {
        int middle_i = (start + end) / 2;
        int prev_i = (middle_i + n - 1) % n;
        int next_i = (middle_i + 1) % n;

        MyPoint prev = conv[prev_i];
        MyPoint next = conv[next_i];
        MyPoint middle = conv[middle_i];

        if (isRightTangent(T, middle, prev, next)) {
            right_i = middle_i;
            break;
        }

        if (middlePointOnGreaterArc(T, middle, next)) {
            if (Orientation(T, middle, conv[start]) < 0 &&
                Orientation(T, conv[start], conv[(start + n - 1) % n]) > 0)
            {
                // first case
                end = middle_i;
            }
            else {
                // second case
                start = middle_i;
            }
        }
        else {
            // smaller arc
            if (Orientation(T, middle, conv[start]) < 0 &&
                Orientation(T, conv[start], conv[(start + n - 1) % n]) < 0)
            {
                // first case
                start = middle_i;
            }
            else {
                // second case
                end = middle_i;
            }
        }
    }

    if (right_i == -1) {
        MyPoint before_start = conv[(start + n - 1) % n];
        MyPoint after_start = conv[(start + 1) % n];
        if (isRightTangent(T, conv[start], before_start, after_start)) {
            right_i = start;
        }
        else {
            right_i = end;
        }
    }

    return { left_i, right_i };
}

void MySegment::Draw(CDC& dc, COLORREF color) const
{
    // Create and select a pen with the given color
    CPen pen(PS_SOLID, 1, color);
    CPen* oldPen = dc.SelectObject(&pen);

    A.Draw(dc);
    B.Draw(dc);

    dc.MoveTo(A.x, A.y);
    dc.LineTo(B.x, B.y);

    // Restore the original pen
    dc.SelectObject(oldPen);
}

void DrawPolygon(CDC& dc, const vector<MyPoint>& points)
{
    int numPoints = points.size();
    if (numPoints == 0)
        return;

    for (int i = 0; i < numPoints; i++)
    {
        size_t nextIndex = (i + 1) % numPoints;
        MySegment edge(points[i], points[nextIndex]);
        edge.Draw(dc);
        points[i].Draw(dc);
    }

    points[0].Draw(dc);
}

double distance(MyPoint A, MyPoint B) {
    return sqrt((A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y));
}

list<int>::iterator moveIteratorForward(list<int>::iterator i, list<int>& L) {
    auto newIt = i;
    newIt++;
    if (newIt == L.end()) return L.begin();
    return newIt;
}

list<int>::iterator moveIteratorBackward(list<int>::iterator i, list<int>& L) {
    if (i == L.begin()) return --L.end();
    auto newIt = i;
    newIt--;
    return newIt;
}

bool doSegmentsIntersect(MySegment s1, MySegment s2) {
    int o1 = Orientation(s1.A, s1.B, s2.A);
    int o2 = Orientation(s1.A, s1.B, s2.B);
    int o3 = Orientation(s2.A, s2.B, s1.A);
    int o4 = Orientation(s2.A, s2.B, s1.B);

    return o1 != o2 && o3 != o4;
}

MyPoint getIntersectionPoint(MySegment seg1, MySegment seg2) {
    MyPoint p1 = seg1.A, q1 = seg1.B;
    MyPoint p2 = seg2.A, q2 = seg2.B;


    double a1 = q1.y - p1.y;
    double b1 = p1.x - q1.x;
    double c1 = a1 * p1.x + b1 * p1.y;

    double a2 = q2.y - p2.y;
    double b2 = p2.x - q2.x;
    double c2 = a2 * p2.x + b2 * p2.y;

    double determinant = a1 * b2 - a2 * b1;

    MyPoint res(0, 0);

    if (determinant != 0) {
        res.x = (c1 * b2 - c2 * b1) / determinant;
        res.y = (a1 * c2 - a2 * c1) / determinant;
        return res;
    }
    throw "No intersection found!";
}

void handleIntersection(int x_sweep_line, MySegment* seg1, MySegment* seg2,
    set<MySegment*, ActiveSegmentsTree>& activeSegments, vector<MyPoint>& intersections,
    priority_queue<pair<MyPoint, pair<MySegment*, MySegment*>>, vector<pair<MyPoint, pair<MySegment*, MySegment*>>>, EventsX>& events) {
    if (doSegmentsIntersect(*seg1, *seg2)) {
        MyPoint intersectionPt(getIntersectionPoint(*seg1, *seg2));
        if (intersectionPt.x <= x_sweep_line) {
            return;
        }
        intersections.push_back(intersectionPt);
        events.push({ intersectionPt, {seg1,seg2} });
    }
}

void MyRectangle::Draw(CDC& dc, COLORREF color, int thickness) const
{
    CPen pen(PS_SOLID, thickness, color);
    CPen* oldPen = dc.SelectObject(&pen);

    CBrush brush(color);
    CBrush* oldBrush = dc.SelectObject(&brush);

    MyPoint gl(xmin, ymin); // top-left
    MyPoint dl(xmin, ymax); // bottom-left
    MyPoint dd(xmax, ymax); // bottom-right
    MyPoint gd(xmax, ymin); // top-right

    vector<MyPoint> rectangle = { gl, dl, dd, gd };
    DrawPolygon(dc, rectangle);

    dc.SelectObject(oldPen);
    dc.SelectObject(oldBrush);
}

bool inBetween(int x, int xmin, int xmax) {
    return x >= xmin && x <= xmax;
}

IntersectionType rectanglesIntersection(MyRectangle rec1, MyRectangle rec2)
{
    int min_left = min(rec1.xmin, rec2.xmin);
    int max_left = max(rec1.xmin, rec2.xmin);
    int min_right = min(rec1.xmax, rec2.xmax);
    int max_right = max(rec1.xmax, rec2.xmax);

    if (max_left > min_right) {
        return EMPTY;
    }

    int min_top = min(rec1.ymin, rec2.ymin);
    int max_top = max(rec1.ymin, rec2.ymin);
    int min_bottom = min(rec1.ymax, rec2.ymax);
    int max_bottom = max(rec1.ymax, rec2.ymax);

    if (max_top > min_bottom) {
        return EMPTY;
    }

    // check whether rec1 is inside of rec2
    if (!inBetween(rec1.xmin, rec2.xmin, rec2.xmax) ||
        !inBetween(rec1.xmax, rec2.xmin, rec2.xmax) ||
        !inBetween(rec1.ymin, rec2.ymin, rec2.ymax) ||
        !inBetween(rec1.ymax, rec2.ymin, rec2.ymax)) {
        return PARTIAL;
    }
    return FULL;
}

bool ptInsideRectangle(MyPoint pt, MyRectangle rec)
{
    return inBetween(pt.x, rec.xmin, rec.xmax) && inBetween(pt.y, rec.ymin, rec.ymax);
}

KDNode* KDTree::constructTree(KDNode* parent, vector<MyPoint>& points, bool isLeftChild)
{
    int n = points.size();
    KDNode* newNode;

    if (n == 0) {
        return nullptr;
    }

    MyRectangle region_parent = parent->region;
    MyRectangle* region;
    NodeType newNodeType;

    if (parent->nodeType == VERTICAL) {
        newNodeType = HORIZONTAL;
        if (isLeftChild) {
            region = new MyRectangle(region_parent.xmin, parent->pt.x, region_parent.ymin, region_parent.ymax);
        }
        else {
            region = new MyRectangle(parent->pt.x, region_parent.xmax, region_parent.ymin, region_parent.ymax);
        }
    }
    else {
        newNodeType = VERTICAL;
        if (isLeftChild) {
            region = new MyRectangle(region_parent.xmin, region_parent.xmax, region_parent.ymin, parent->pt.y);
        }
        else {
            region = new MyRectangle(region_parent.xmin, region_parent.xmax, parent->pt.y, region_parent.ymax);
        }
    }

    if (n == 1) {
        newNode = new KDNode(parent, LEAF, *region, nullptr, nullptr, points[0]);
        return newNode;
    }

    if (newNodeType == VERTICAL) {
        sort(points.begin(), points.end());
    }
    else {
        sort(points.begin(), points.end(), [](MyPoint t1, MyPoint t2) {return t1.y < t2.y; });
    }

    int middleIndex = (n - 1) / 2;
    vector<MyPoint> leftPoints(middleIndex + 1);
    vector<MyPoint> rightPoints(n - middleIndex - 1);

    copy(points.begin(), points.begin() + middleIndex + 1, leftPoints.begin());
    copy(points.begin() + middleIndex + 1, points.end(), rightPoints.begin());

    newNode = new KDNode(parent, newNodeType, *region, nullptr, nullptr, points[middleIndex]);
    KDNode* leftChild = constructTree(newNode, leftPoints, true);
    KDNode* rightChild = constructTree(newNode, rightPoints, false);

    newNode->leftChild = leftChild;
    newNode->rightChild = rightChild;
    return newNode;
}

void KDTree::Draw(CDC& dc, KDNode* node, bool isStart) const
{
    if (isStart) {
        node = rootNode;
    }
    if (node == nullptr) {
        return;
    }

    drawLine(dc, node);
    Draw(dc, node->leftChild, false);
    Draw(dc, node->rightChild, false);
}

void KDTree::addLeaves(KDNode* node, vector<MyPoint>& points)
{
    if (node) {
        if (node->nodeType == LEAF) {
            points.push_back(node->pt);
        }
        addLeaves(node->leftChild, points);
        addLeaves(node->rightChild, points);
    }
}

KDTree::KDTree(vector<MyPoint>& points, int length, int width)
{
    int n = points.size();
    if (n == 0) {
        return;
    }
    if (n == 1) {
        rootNode = new KDNode(nullptr, LEAF, MyRectangle(0, length, 0, width), nullptr, nullptr, points[0]);
    }
    else {
        sort(points.begin(), points.end());
        int middleIndex = (n - 1) / 2;
        vector<MyPoint> leftPoints(middleIndex + 1);
        vector<MyPoint> rightPoints(n - middleIndex - 1);

        copy(points.begin(), points.begin() + middleIndex + 1, leftPoints.begin());
        copy(points.begin() + middleIndex + 1, points.end(), rightPoints.begin());

        rootNode = new KDNode(nullptr, VERTICAL, MyRectangle(0, length, 0, width), nullptr, nullptr, points[middleIndex]);
        KDNode* leftChild = constructTree(rootNode, leftPoints, true);
        KDNode* rightChild = constructTree(rootNode, rightPoints, false);

        rootNode->leftChild = leftChild;
        rootNode->rightChild = rightChild;
    }
}

void KDTree::drawLine(CDC& dc, KDNode* node) const
{
    if (node) {
        if (node->nodeType == VERTICAL) {
            int x = node->pt.x;
            int ymin = node->region.ymin;
            int ymax = node->region.ymax;

            MySegment d(MyPoint(x, ymin), MyPoint(x, ymax));
            d.Draw(dc, RGB(0,0,255));
        }
        else if (node->nodeType == HORIZONTAL) {
            int y = node->pt.y;
            int xmin = node->region.xmin;
            int xmax = node->region.xmax;

            MySegment d(MyPoint(xmin, y), MyPoint(xmax, y));
            d.Draw(dc, RGB(0,0,255));
        }
        else {
            node->pt.Draw(dc, RGB(255,0,0), 4);
        }
    }
}

void KDTree::query(MyRectangle rec, vector<MyPoint>& queryPoints, KDNode* node, bool isStart)
{
    if (isStart) {
        node = rootNode;
    }
    if (node == nullptr) {
        return;
    }

    if (node->nodeType == LEAF) {
        if (ptInsideRectangle(node->pt, rec)) {
            queryPoints.push_back(node->pt);
        }
        return;
    }
    if (node->leftChild) {
        IntersectionType type = rectanglesIntersection(node->leftChild->region, rec);
        if (type == PARTIAL) {
            query(rec, queryPoints, node->leftChild, false);
        }
        else if (type == FULL) {
            addLeaves(node->leftChild, queryPoints);
            //queryPoints.push_back(node->pt);
        }
    }

    if (node->rightChild) {
        IntersectionType type = rectanglesIntersection(node->rightChild->region, rec);
        if (type == PARTIAL) {
            query(rec, queryPoints, node->rightChild, false);
        }
        else if (type == FULL) {
            addLeaves(node->rightChild, queryPoints);
        }
    }

}
