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

void __fastcall TGrahamScan::GeneratePointsClick(TObject *Sender)
{
return;
}
//---------------------------------------------------------------------------

void __fastcall TGrahamScan::ClearClick(TObject *Sender)
{
return;
}
//---------------------------------------------------------------------------

void __fastcall TGrahamScan::GrahamScanClick(TObject *Sender)
{
return;
}
//---------------------------------------------------------------------------

