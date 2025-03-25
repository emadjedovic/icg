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
    MyPoint p(X, Y);
    points.push_back(p);
    p.Draw(Image);
}
//---------------------------------------------------------------------------

void __fastcall TICG_app::ButtonSimplePolygonClick(TObject* Sender)
{
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

    // Moves to a point and draws a line to the next point.
    for (int i = 0; i < points.size() - 1; i++) {
        Image->Canvas->MoveTo(points[i].x, points[i].y);
        Image->Canvas->LineTo(points[i + 1].x, points[i + 1].y);
    }

    // connects the last point back to the first to complete the polygon
    Image->Canvas->LineTo(points[0].x, points[0].y);
}
//---------------------------------------------------------------------------

