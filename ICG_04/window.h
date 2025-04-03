//---------------------------------------------------------------------------

#ifndef WindowH
#define WindowH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <helper.h>

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
  public: // User declarations
    __fastcall TTriangulation(TComponent* Owner);
};

int numPoints(0);
int numDiagonals(0);
int numSides(0);
MyPoint polygon[500];
MySide sides[500];
MyDiagonal diagonals[500];

//---------------------------------------------------------------------------
extern PACKAGE TTriangulation* Triangulation;
//---------------------------------------------------------------------------
#endif

