//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "window.h"
#include <algorithm>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TICG_app* ICG_app;
//---------------------------------------------------------------------------
__fastcall TICG_app::TICG_app(TComponent* Owner) : TForm(Owner)
{
    // Sets the brush color to white.
    Image->Canvas->Brush->Color = clWhite;

    // Fills the entire image area with a white background.
    Image->Canvas->FillRect(TRect(0, 0, Image->Width, Image->Height));

    // Sets the brush color to black.
    Image->Canvas->Brush->Color = clBlack;

    // Draws a black border (frame) around the image area.
    Image->Canvas->FrameRect(TRect(0, 0, Image->Width, Image->Height));
}
//---------------------------------------------------------------------------
void __fastcall TICG_app::ImageMouseDown(
    TObject* Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    MyPoint newPoint(X, Y);

    if (RadioAddSegment->Checked) {
        if (second_click) {
            MySegment newSegment(points[points.size() - 1], newPoint);
            newSegment.Draw(Image);
            segments.push_back(newSegment);
        }
        second_click = !second_click;
    } else if (RadioPointInCH->Checked) {
        if (CH.size() >= 3) {
            if (PointInPolygon(CH, newPoint))
                ShowMessage("Inside the Convex Hull!");
            else
                ShowMessage("Outside the Convex Hull!");
        }
    }

    points.push_back(newPoint);
    newPoint.Draw(Image);
}
//---------------------------------------------------------------------------

void __fastcall TICG_app::ButtonSimplePolygonClick(TObject* Sender)
{
    if (points.size() < 3)
        return;

    // finds the leftmost point (i.e., the point with the smallest x-coordinate)
    for (int i = 1; i < points.size(); i++) {
        if (points[i] < points[0]) {
            swap(points[i], points[0]);
        }
    }

    MyPoint leftmost(points[0]);
    // sorts the remaining points (excluding the first one) clockwise around the leftmost point
    sort(points.begin() + 1, points.end(), [leftmost](MyPoint A, MyPoint B) {
        return Orientation(leftmost, A, B) < 0;
    });

    DrawPolygon(Image, points, clBlue);
}
//---------------------------------------------------------------------------

void TICG_app::ClearScreen()
{
    Image->Canvas->Brush->Color = clWhite;
    Image->Canvas->FillRect(TRect(0, 0, Image->Width, Image->Height));

    Image->Canvas->Brush->Color = clBlack;
    Image->Canvas->FrameRect(TRect(0, 0, Image->Width, Image->Height));

    points.clear();
    segments.clear();
    CH.clear();
}

void __fastcall TICG_app::ButtonClearClick(TObject* Sender)
{
    ClearScreen();
}

//---------------------------------------------------------------------------

void __fastcall TICG_app::ButtonGeneratePointsClick(TObject* Sender)
{
    ClearScreen();
    int n = EditGeneratePoints->Text.ToInt();
    for (int i = 0; i < n; i++) {
        int x =
            rand() %
            Image->Width; // integer from 0 up to one less than the image width
        int y =
            rand() %
            Image
                ->Height; // integer from 0 up to one less than the image height
        MyPoint newPoint(x, y);
        newPoint.Draw(Image, clBlue);
        points.push_back(newPoint);
    }
}

//---------------------------------------------------------------------------

void __fastcall TICG_app::ButtonDoSegmentsIntersectClick(TObject* Sender)
{
    if (segments.size() < 2)
        return;

    int n = segments.size();

    MySegment s1 = segments[n - 1]; // the last one
    MySegment s2 = segments[n - 2]; // the second last

    int o1(Orientation(s1.A, s1.B, s2.A));
    int o2(Orientation(s1.A, s1.B, s2.B));
    int o3(Orientation(s2.A, s2.B, s1.A));
    int o4(Orientation(s2.A, s2.B, s1.B));

    if (o1 != o2 && o3 != o4) {
        ShowMessage("Segments intersect!");
    } else {
        ShowMessage("Segments don't intersect!");
    }
}
//---------------------------------------------------------------------------

void __fastcall TICG_app::ButtonGiftWrappingClick(TObject* Sender)
{
    if (points.size() < 3)
        return;

    // Find the leftmost (smallest x-value) point
    for (int i = 1; i < points.size(); i++)
        if (points[i] < points[0])
            swap(points[i], points[0]);

    // Initialize the convex hull with the leftmost point
    MyPoint pivot(points[0]);
    CH.push_back(pivot);

    while (true) {
        MyPoint P = points[0];
        if (P == pivot)
            P = points[1];

        for (int i = 0; i < points.size(); i++)
            if (Orientation(pivot, P, points[i]) > 0)
                P = points[i];

        pivot = P;

        // If we have wrapped around to the first point, the hull is complete
        if (pivot == points[0])
            break;

        CH.push_back(P);
    }

    DrawPolygon(Image, CH, clRed);
}
//---------------------------------------------------------------------------

void __fastcall TICG_app::ButtonGrahamScanClick(TObject* Sender)
{
CH.clear();
    if (points.size() < 3)
        return;

    // leftmost point
    for (int i = 1; i < points.size(); i++) {
        if (points[i] < points[0])
            swap(points[i], points[0]);
    }

    MyPoint leftmost(points[0]);

    // sort by angle
    sort(points.begin() + 1, points.end(), [leftmost](MyPoint A, MyPoint B) {
        return Orientation(leftmost, A, B) < 0;
    });

    CH.push_back(leftmost);
    CH.push_back(points[1]);

    int prevIndex = 0;
    int currIndex = 1;

    for (int i = 2; i < points.size(); i++) {
        MyPoint nextPoint = points[i];

        if (Orientation(CH[prevIndex], CH[currIndex], nextPoint) < 0)
            CH.push_back(nextPoint);
        else {
            while (Orientation(CH[prevIndex], CH[currIndex], nextPoint) > 0) {
                CH.pop_back();
                currIndex--;
                prevIndex--;
            }
            CH.push_back(nextPoint);
        }
        currIndex++;
        prevIndex++;
    }

    DrawPolygon(Image, CH, clRed);
}
//---------------------------------------------------------------------------

