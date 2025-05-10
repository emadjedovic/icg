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

void MyPoint::Draw(CDC& dc) const
{
    dc.Ellipse(x - 3, y - 3, x + 3, y + 3);
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

void MySegment::Draw(CDC& dc) const
{
    A.Draw(dc);
    B.Draw(dc);

    dc.MoveTo(A.x, A.y);
    dc.LineTo(B.x, B.y);
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

    points[0].Draw(dc); // Ensure the first point is drawn again
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