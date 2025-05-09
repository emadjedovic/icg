//---------------------------------------------------------------------------

#ifndef windowH
#define windowH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Dialogs.hpp> // Required for ShowMessage
#include <System.SysUtils.hpp> // Required for IntToStr
#include <helper.h>
#include <vector>

using namespace std;
//---------------------------------------------------------------------------
class TICG_app : public TForm
{
  __published: // IDE-managed Components
    TImage* Image;

    TButton* ButtonSimplePolygon;
    TButton* ButtonDoSegmentsIntersect;
    TButton* ButtonGiftWrapping;
    TButton* ButtonClear;
    TButton *ButtonGrahamScan;
    TButton *ButtonIncrementalConvex;

    TEdit* EditGeneratePoints;
    TButton* ButtonGeneratePoints;
    TRadioButton* RadioAddPoint;
    TRadioButton* RadioAddSegment;
    TRadioButton *RadioPointInCH;
    TRadioButton *RadioDrawTangents;

    void __fastcall ImageMouseDown(
        TObject* Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall ButtonSimplePolygonClick(TObject* Sender);
    void __fastcall ButtonDoSegmentsIntersectClick(TObject* Sender);
    void __fastcall ButtonGiftWrappingClick(TObject* Sender);
    void __fastcall ButtonClearClick(TObject* Sender);
    void __fastcall ButtonGeneratePointsClick(TObject* Sender);
    void __fastcall ButtonGrahamScanClick(TObject *Sender);
    void __fastcall ButtonIncrementalConvexClick(TObject *Sender);

  private: // User declarations
  public: // User declarations

    __fastcall TICG_app(TComponent* Owner);
    void ClearScreen();

    vector<MyPoint> points;
    vector<MySegment> segments;
    vector<MyPoint> CH;
    bool second_click = false;
};
//---------------------------------------------------------------------------
extern PACKAGE TICG_app* ICG_app;
//---------------------------------------------------------------------------
#endif

