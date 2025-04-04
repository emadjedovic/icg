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
#include <Ear.h>
#include <Diagonal.h>
#include <set>

using namespace std;

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
    ~TTriangulation();
};

int AreaPoly2(int, const MyPoint[100]);
bool XOR(bool, bool);
int remainder(int, int);
bool firstSubsetofSecond(int[3], int[3]);

bool Diagonal_IE(int, int, int, MyPoint[100]);
bool Diagonal(int, int, int, MyPoint[100]);
bool InCone(int, int, int, MyPoint[100]);
void ClipEar(int, int, MyPoint[100]);

int missingElement(int[10], int[10]);

void endpoints(struct Diagonal diag, int[2], int[3]);
void triangulate(int, MyPoint[500]);
int clear();
int numPoints;
int numDiagonals;
int numEars;
MyPoint polygon[500];
Ear ears[500];
Diagonal diagonals[500];
Graphics::TBitmap* bmp;
TCanvas* canvas;

//---------------------------------------------------------------------------
extern PACKAGE TTriangulation* Triangulation;
//---------------------------------------------------------------------------
#endif

