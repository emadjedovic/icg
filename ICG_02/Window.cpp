//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Window.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TGrahamScan* GrahamScan;

//---------------------------------------------------------------------------
__fastcall TGrahamScan::TGrahamScan(TComponent* Owner) : TForm(Owner) {}
//---------------------------------------------------------------------------
void __fastcall TGrahamScan::FormActivate(TObject* Sender)
{
    Image->Canvas->Brush->Color = clBlack;
    Image->Canvas->FillRect(Image->ClientRect);
}
//---------------------------------------------------------------------------

void __fastcall TGrahamScan::ImageMouseDown(
    TObject* Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    Image->Canvas->Pen->Color = clRed;
    Image->Canvas->Ellipse(X - 3, Y - 3, X + 3, Y + 3);
    pointList.push_back(MyPoint(X, Y));
}
//---------------------------------------------------------------------------

void __fastcall TGrahamScan::GeneratePointsButtonClick(TObject* Sender)
{
    // clear the canvas first
    Image->Canvas->Brush->Color = clBlack;
    Image->Canvas->FillRect(Image->ClientRect);

    pointList.clear();

    // ensures that the random number generator produces different results
    // every time the program runs, by setting the seed for the random
    // number generator using the current time
    srand(time(0));

    // runs a number of times determined by the value in the Edit component
    int pointCount = Edit->Text.ToInt();

    int widthLimit = Image->Width - 100;
    int heightLimit = Image->Height - 100;

    int xOffset = 60; // Constant for the x-offset
    int yOffset = 60; // Constant for the y-offset

    for (int i = 0; i < pointCount; i++) {
        int randomX = xOffset + rand() % widthLimit; // X coordinate with offset
        int randomY =
            yOffset + rand() % heightLimit; // Y coordinate with offset
        MyPoint newPoint = MyPoint(randomX, randomY); // Create the point
        pointList.push_back(newPoint); // Add point to the list
    }

    DrawPointList(Image, pointList, clRed);
}
//---------------------------------------------------------------------------

void __fastcall TGrahamScan::ClearButtonClick(TObject* Sender)
{
    Image->Canvas->Brush->Color = clBlack;
    Image->Canvas->FillRect(Image->ClientRect);

    pointList.clear();
}
//---------------------------------------------------------------------------

void __fastcall TGrahamScan::GrahamScanButtonClick(TObject* Sender)
{
    list<MyPoint> Hull = GrahamScan(pointList);

    Image->Canvas->MoveTo(Hull.front().x, Hull.front().y);

    list<MyPoint>::iterator i = ++Hull.begin();

    while (i != Hull.end()) {
        MyPoint nextPoint = (*i);
        Image->Canvas->LineTo(nextPoint.x, nextPoint.y);
        i++;
    }
}
//---------------------------------------------------------------------------

list<MyPoint> TGrahamScan::GrahamScan(list<MyPoint> L)
{
    L.sort(Criterion);
    MyPoint firstPoint = *L.begin();
    MyPoint secondPoint = *(++L.begin());

    list<MyPoint>::iterator i;

    stack<MyPoint> upperstack;
    stack<MyPoint> lowerstack;

    // Build the upper hull
    upperstack.push(firstPoint);
    upperstack.push(secondPoint);
    i = L.begin();
    advance(i, 2); // third point

    while (i != L.end()) {
        MyPoint next = *i;
        // Ensure at least 3 points for orientation check
        while (upperstack.size() >= 2) {
            MyPoint current = upperstack.top();
            upperstack.pop();
            MyPoint previous = upperstack.top();
            upperstack.push(current); // Restore the top point
            // Check orientation
            if (Orientation(previous, current, next) >= 0)
                upperstack.pop();
            else
                break;
        }

        upperstack.push(next);
        i++;
    }

    // Build the lower hull
    lowerstack.push(firstPoint);
    lowerstack.push(secondPoint);
    i = L.begin();
    advance(i, 2); // third point

    while (i != L.end()) {
        MyPoint next = *i;
        // Ensure at least 3 points for orientation check
        while (lowerstack.size() >= 2) {
            MyPoint current = lowerstack.top();
            lowerstack.pop();
            MyPoint previous = lowerstack.top();
            lowerstack.push(current); // Restore the top point
            // Check orientation
            if (Orientation(previous, current, next) <= 0)
                lowerstack.pop();
            else
                break;
        }

        lowerstack.push(next);
        i++;
    }

    // combine the two hulls
    list<MyPoint> hullList;

    // reverse the upperstack
    stack<MyPoint> tempStack;
    while (!upperstack.empty()) {
        tempStack.push(upperstack.top());
        upperstack.pop();
    }
    while (!tempStack.empty()) {
        hullList.push_back(tempStack.top());
        tempStack.pop();
    }

    // now the rightmost is the last in the hullList

    lowerstack.pop();
    while (!lowerstack.empty()) {
        hullList.push_back(lowerstack.top());
        lowerstack.pop();
    }

    return hullList;
}

