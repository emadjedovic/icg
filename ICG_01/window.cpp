//---------------------------------------------------------------------------

#include <vcl.h>
#include <list>
#include <algorithm>
#pragma hdrstop

#include "window.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

using namespace std;

TMyApp* MyApp;

struct MyPoint
{
    float x, y;
    char c; // a label
};

struct MyLine
{
    MyPoint p1, p2;
};

// Polygon as an array of points
MyPoint polygon[100];
// General collection of points
MyPoint points[1000];
int numPoints = 0;
int lastPointIndex;

// calculates the angle between a line defined by two points
// and the positive x-axis
float angle(MyPoint p1, MyPoint p2)
{
    float dx, dy, angle;
    dx = p2.x - p1.x;
    dy = p2.y - p1.y;

    if ((p1.x - p2.x) == 0)
        angle = 90;
    if ((p1.x < p2.x) && (p1.y <= p2.y))
        angle = ((atan(dy / dx) * 180.0) / (4 * atan(1.)));
    if ((p1.x > p2.x) && (p1.y > p2.y))
        angle = 180 + ((atan(dy / dx) * 180.0) / (4 * atan(1.)));
    if ((p1.x > p2.x) && (p1.y < p2.y))
        angle = 180 - ((atan(-dy / dx) * 180.0) / (4 * atan(1.)));
    if ((p1.x < p2.x) && (p1.y > p2.y))
        angle = 360 - ((atan(-dy / dx) * 180.0) / (4 * atan(1.)));

    return angle;
};

// removes jth member from an array of points
int removeMember(MyPoint points[], int n, int j)
{
    int k = j;
    while (k < n) {
        int nextIndex = k + 1;
        MyPoint nextPoint = points[nextIndex];
        points[k] = nextPoint;
        k++;
    }
    return n - 1;
};

// removes all points from the array where y is less than or
// equal to the y of the j-th point in the array
int removeLowerPoints(MyPoint points[], int n, int j)
{
    int lowerBound = points[j].y;
    int counter = 0;
    MyPoint* newPoints = new MyPoint[n];
    for (int i = 0; i < n; i++) {
        // Keep only points above
        if (points[i].y > lowerBound) {
            newPoints[counter] = points[i];
            counter++;
        }
    }

    for (int i = 0; i < counter; i++) {
        points[i] = newPoints[i];
    }

    delete[] newPoints;
    return counter;
};

/*
void sort1(MyPoint a[], int n)
{
          int i,j,t,p ;
 for(i=n-1;i>=0;i--)
   for(j=1;j<=i;j++)
    if(a[j-1].x>a[j].x)
    {
	 t=a[j-1].x;
     p=a[j-1].y;
     a[j-1].x=a[j].x;
     a[j-1].y=a[j].y;
     a[j].x=t;
     a[j].y=p;
    };
}
*/

// left points go first
bool criterion(MyPoint p1, MyPoint p2)
{
    return p1.x < p2.x;
}

// finds the lowest point, places it on the first position,
// and returns the index of the highest point
int pointMinY(MyPoint points[], int n)
{
    // sort   ?

    int ymin = points[0].y;
    int indexMin = 0; // At the end, j holds the index of the lowest point
    for (int i = 0; i < n; i++) {
        if (ymin > points[i].y) {
            ymin = points[i].y;
            indexMin = i;
        }
    }

    MyPoint temp = points[0];
    points[0] = points[indexMin];
    points[indexMin] = temp;

    int ymax = points[0].y;
    int indexMax = 0; // At the end, k holds the index of the highest point
    for (int i = 0; i < n; i++) {
        if (ymax < points[i].y) {
            ymax = points[i].y;
            indexMax = i;
        }
    }

    // all points have the same y coordinate?
    if (ymax == ymin)
        return (n - 1);
    else
        return indexMax;
}

// Separates points into two disjoint sets � those to the left and those to the right
// of the line defined by the points with the maximum and minimum y-coordinates
void seperate(MyPoint points[], MyPoint pointsLeft[], MyPoint pointsRight[],
    int n, int &numLeft, int &numRight)
{
    // pointMinY finds the lowest point, places it on the first position,
    // and returns the index of the highest point
    int maxYindex = pointMinY(points, n);

    MyPoint lowestPoint = points[0];
    MyPoint highestPoint = points[maxYindex];

    pointsLeft[0] = lowestPoint;
    pointsRight[0] = lowestPoint;

    // the seperation line looks like _/_
    int signal = 1;
    // the seperation like looks like _\_
    if (lowestPoint.x > highestPoint.x)
        signal = -1;

    int indexLeft = 1, indexRight = 1;
    float y;

    // for each point...
    for (int i = 1; i < n; i++) {
        if ((highestPoint.x - lowestPoint.x) != 0) {
            // not a vertical line
            y = lowestPoint.y + ((highestPoint.y - lowestPoint.y) *
                                    (points[i].x - lowestPoint.x)) /
                                    (highestPoint.x - lowestPoint.x);

            if (signal * (y - points[i].y) > 0) {
                pointsLeft[indexLeft] = points[i];
                indexLeft++;
            }
            if (signal * (y - points[i].y) < 0) {
                pointsRight[indexRight] = points[i];
                indexRight++;
            }
        } else {
            // handling vertical line case
            if (points[i].x > lowestPoint.x && i != 0) {
                pointsLeft[indexLeft] = points[i];
                indexLeft++;
            }
            if (points[i].x < lowestPoint.x && i != maxYindex) {
                pointsRight[indexRight] = points[i];
                indexRight++;
            }
        }
    }

    pointsLeft[indexLeft] = highestPoint;
    pointsRight[indexRight] = highestPoint;
    numLeft = indexLeft + 1;
    numRight = indexRight + 1;
}

int Hull(MyPoint points[], int n, MyPoint contour[], int signal)
{
    MyPoint* remainingPoints = new MyPoint[n];
    MyPoint* anglesList = new MyPoint[n];

    for (int i = 0; i < n; i++)
        remainingPoints[i] = points[i];

    int remainingCount = n, hullSize = 0;

    MyPoint lastPoint = points[n - 1];
    MyPoint currentPoint = remainingPoints[0];
    MyPoint startPoint = currentPoint;

    contour[hullSize++] = currentPoint;

    // Remove the first point from the set of remaining points.
    remainingCount = removeMember(remainingPoints, n, 0);

    while (currentPoint.x != lastPoint.x || currentPoint.y != lastPoint.y) {
        // Compute angles between the current point and remaining candidates.
        for (int candidateIndex = 0; candidateIndex < remainingCount;
             candidateIndex++) {
            if (signal)
                anglesList[candidateIndex].x =
                    angle(currentPoint, remainingPoints[candidateIndex]);
            else
                anglesList[candidateIndex].x =
                    180 - angle(currentPoint, remainingPoints[candidateIndex]);

            // Store the index of each point in `y` for sorting.
            anglesList[candidateIndex].y = candidateIndex;
        }

        sort(anglesList, anglesList + remainingCount, criterion);
        // Select the smallest angle.
        int nextIndex = int(anglesList[0].y);
        contour[hullSize++] = remainingPoints[nextIndex];

        // Move to the next point in the hull.
        currentPoint = remainingPoints[nextIndex];
        if(currentPoint.y == lastPoint.y || currentPoint.y == startPoint.y)
        {
         remainingCount = removeMember(remainingPoints, remainingCount, nextIndex);
        } else
        {

        // Remove the chosen point from the remaining candidates.
            remainingCount = removeLowerPoints(remainingPoints, remainingCount, nextIndex);
        }

    }

    contour[hullSize] = lastPoint;
    return hullSize + 1;
}

void path(MyPoint points[], int n, MyPoint outputPoints[])
{
    MyPoint* angles = new MyPoint[n - 1];
    // find the lowest point (will be at points[0] after this call
    pointMinY(points, n);

    for (int j = 1; j < n; j++) {
        angles[j - 1].x = angle(points[0], points[j]); // store the angle
        angles[j - 1].y = j; // store the index
    }

    sort(angles, angles + n - 1, criterion);

    // Place the lowest point as the first point in the path
    outputPoints[0].x = points[0].x;
    outputPoints[0].y = points[0].y;

    // the rest
    for (int i = 1; i < n; i++) {
        int sortedIndex = int(angles[i - 1].y); // Retrieve original index
        outputPoints[i].x = points[sortedIndex].x;
        outputPoints[i].y = points[sortedIndex].y;
    }

    // close the path
    outputPoints[n].x = points[0].x;
    outputPoints[n].y = points[0].y;

    delete[] angles;
}

//---------------------------------------------------------------------------
__fastcall TMyApp::TMyApp(TComponent* Owner) : TForm(Owner)
{
    // no need for any change
}

//---------------------------------------------------------------------------
void __fastcall TMyApp::FormActivate(TObject* Sender)
{
    Image->Canvas->Brush->Color = clBlack;
    Image->Canvas->FillRect(MyApp->Image->ClientRect);
}
//---------------------------------------------------------------------------
void __fastcall TMyApp::ClearClick(TObject* Sender)
{
    lastPointIndex = 0; // zero points
    Image->Canvas->Brush->Color = clBlack;
    Image->Canvas->FillRect(MyApp->Image->ClientRect);
}

//---------------------------------------------------------------------------
void __fastcall TMyApp::ImageMouseDown(
    TObject* Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    MyPoint p1;
    Image->Canvas->Pen->Color = clRed;
    Image->Canvas->Ellipse(X - 3, Y - 3, X + 3, Y + 3);
    p1.x = X;
    p1.y = Y;
    points[lastPointIndex++] = p1;
    numPoints = lastPointIndex;
}
//---------------------------------------------------------------------------

void __fastcall TMyApp::SimplePathClick(TObject* Sender)
{
    int i;
    // hold a sequence of points
    MyPoint* a = new MyPoint[numPoints + 1];
    path(points, numPoints, a);

    Image->Canvas->Pen->Color = clRed;
    // refresh or reinitialize the form
    FormActivate(this);

    // loop to draw points
    for (int i = 0; i < numPoints; i++) {
        Image->Canvas->Ellipse(
            points[i].x - 3, points[i].y - 3, points[i].x + 3, points[i].y + 3);
        Image->Canvas->Pen->Color = clWhite;
        Image->Canvas->MoveTo(a[0].x, a[0].y);

        for (int j = 1; j <= numPoints; j++) {
            // draws a line from the current position to the next point
            Image->Canvas->LineTo(a[j].x, a[j].y);
        }

        Image->Canvas->Pen->Color = clRed;

        delete[] a;
    }
}
//---------------------------------------------------------------------------

void __fastcall TMyApp::ConvexHullClick(TObject* Sender)
{
    // hold points in different stages of processing the convex hull algorithm
    MyPoint* points1 = new MyPoint[numPoints + 1];
    MyPoint* points2 = new MyPoint[numPoints + 1];

    int counter1 = 0, counter2 = 0;

    seperate(points, points1, points2, numPoints, counter1, counter2);

    MyPoint* a2 = new MyPoint[counter1];
    MyPoint* a1 = new MyPoint[numPoints + 1];

    int k = Hull(points1, counter1, a2, 1);
    int k1 = Hull(points2, counter2, a1, 0);

    int z = k1;

    for (int i = k - 2; i >= 0; i--) {
        a1[z].x = a2[i].x;
        a1[z].y = a2[i].y;
        z = z + 1;
    }

    // refresh the form/redraw the canvas/update the UI
    FormActivate(this);

    for (int i = 0; i < numPoints; i++) {
        Image->Canvas->Ellipse(
            points[i].x - 3, points[i].y - 3, points[i].x + 3, points[i].y + 3);
    }
    Image->Canvas->Pen->Color = clWhite;
    Image->Canvas->MoveTo(a1[0].x, a1[0].y);

    for (int i = 1; i < z; i++)
        Image->Canvas->LineTo(a1[i].x, a1[i].y);

    Image->Canvas->Pen->Color = clRed;

    delete[] points1;
    delete[] points2;
    delete[] a2;
    delete[] a1;
}
//---------------------------------------------------------------------------

