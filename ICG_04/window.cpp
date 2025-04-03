//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Window.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TTriangulation* Triangulation;

//---------------------------------------------------------------------------

__fastcall TTriangulation::TTriangulation(TComponent* Owner) :
    TForm(Owner), numPoints(0), numDiagonals(0), numSides(0),
    bmp(new Graphics::TBitmap), canvas(new TCanvas())
{
}

//---------------------------------------------------------------------------

TTriangulation::~TTriangulation()
{
    if (bmp) {
        delete bmp;
    }
    if (canvas) {
        delete canvas;
    }
}

//---------------------------------------------------------------------------
void __fastcall TTriangulation::ImageMouseDown(
    TObject* Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    return;
}
//---------------------------------------------------------------------------

void __fastcall TTriangulation::ButtonTriangulationClick(TObject* Sender)
{
    return;
}
//---------------------------------------------------------------------------

void __fastcall TTriangulation::ButtonClearClick(TObject* Sender)
{
    canvas->Brush->Color = clWhite;
    canvas->FillRect(Image->ClientRect);
    numPoints = 0;
    numSides = 0;
    numDiagonals = 0;
}
//---------------------------------------------------------------------------

void __fastcall TTriangulation::ButtonImproveClick(TObject* Sender)
{
    return;
}
//---------------------------------------------------------------------------

void __fastcall TTriangulation::FormCreate(TObject* Sender)
{
    canvas = Image->Canvas;
    canvas->Brush->Color = clWhite;
    canvas->FillRect(Image->ClientRect);
    numPoints = 0;
}
//---------------------------------------------------------------------------

