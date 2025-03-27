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

void __fastcall TGrahamScan::GeneratePointsClick(TObject* Sender)
{
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

    DrawPointList(pointList, clRed);
}
//---------------------------------------------------------------------------

void __fastcall TGrahamScan::ClearClick(TObject* Sender)
{
    Image->Canvas->Brush->Color = clBlack;
    Image->Canvas->FillRect(Image->ClientRect);

    pointList.clear();
}
//---------------------------------------------------------------------------

void __fastcall TGrahamScan::GrahamScanClick(TObject* Sender)
{
    return;
}
//---------------------------------------------------------------------------

