//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "window.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TApp *App;
//---------------------------------------------------------------------------
__fastcall TApp::TApp(TComponent* Owner)
    : TForm(Owner)
{
canvas=Image->Canvas;
Empty->Assign(Image->Picture->Graphic);
}
}
//---------------------------------------------------------------------------
void __fastcall TApp::ImageClick(TObject *Sender)
{
return;
}
//---------------------------------------------------------------------------
void __fastcall TApp::ButtonConvexHullClick(TObject *Sender)
{
return;
}
//---------------------------------------------------------------------------
void __fastcall TApp::ButtonGeneratePointsClick(TObject *Sender)
{
return;
}
//---------------------------------------------------------------------------
void __fastcall TApp::ButtonClearClick(TObject *Sender)
{
                      return;
}
//---------------------------------------------------------------------------
void __fastcall TApp::CheckBoxProcedureClick(TObject *Sender)
{
return;
}
//---------------------------------------------------------------------------
