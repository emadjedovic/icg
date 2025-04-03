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

int Area2(const MyPoint &, const MyPoint &, const MyPoint &);
int AreaPoly2(int, const MyPoint[100]);
bool XOR(bool, bool);
bool IntersectProp(
    const MyPoint &, const MyPoint &, const MyPoint &, const MyPoint &);
bool Left(const MyPoint &, const MyPoint &, const MyPoint &);
bool LeftOn(const MyPoint &, const MyPoint &, const MyPoint &);
bool Collinear(const MyPoint &, const MyPoint &, const MyPoint &);
void SubVector(const MyPoint &, const MyPoint &, MyPoint &);
int Dot(const MyPoint &, const MyPoint &);
int Length2(const MyPoint &);
bool IsPointOnSegment(const MyPoint &, const MyPoint &, const MyPoint &);
bool Intersect(MyPoint, MyPoint, MyPoint, MyPoint);
bool Diagonalie(int, int, int, MyPoint[100]);
bool Diagonal(int, int, int, MyPoint[100]);
void PointAssign(MyPoint*, MyPoint*);
bool InCone(int, int, int, MyPoint[100]);
void ClipEar(int, int, MyPoint[100]);

//---------------------------------------------------------------------------
extern PACKAGE TTriangulation* Triangulation;
//---------------------------------------------------------------------------
#endif

