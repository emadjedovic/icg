//---------------------------------------------------------------------------

#ifndef WindowH
#define WindowH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Helper.h>
#include <MyPoint.h>
#include <MySide.h>
#include <MyDiagonal.h>

//---------------------------------------------------------------------------
class TTriangulation : public TForm
{
  __published: // IDE-managed Components
    TImage* Image;
    TButton* ButtonTriangulation;
    TButton* ButtonImprove;
    TButton* ButtonClear;
    TCheckBox* CheckBoxProcedure;
    void __fastcall ImageMouseDown(
        TObject* Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall ButtonTriangulationClick(TObject* Sender);
    void __fastcall ButtonClearClick(TObject* Sender);
    void __fastcall ButtonImproveClick(TObject* Sender);
    void __fastcall FormCreate(TObject* Sender);
  private: // User declarations
    int numPoints;
    int numDiagonals;
    int numSides;
    MyPoint polygon[500];
    MySide sides[500];
    MyDiagonal diagonals[500];
    Graphics::TBitmap* bmp;
    TCanvas* canvas;
  public: // User declarations
    __fastcall TTriangulation(TComponent* Owner);
    ~TTriangulation();
};

//---------------------------------------------------------------------------
extern PACKAGE TTriangulation* Triangulation;
//---------------------------------------------------------------------------
#endif

