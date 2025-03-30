//---------------------------------------------------------------------------

#ifndef windowH
#define windowH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.ExtCtrls.hpp>

#include <stack>
#include <vector>
#include <MyPoint.h>
#include <algorithm>

using namespace std;

TCanvas* canvas = 0;
Graphics::TBitmap* Empty = new Graphics::TBitmap();
Graphics::TBitmap* Image = new Graphics::TBitmap();

bool procedure = false;

//---------------------------------------------------------------------------
class TApp : public TForm
{
  __published: // IDE-managed Components
    TImage* Image;
    TButton* ButtonConvexHull;
    TButton* ButtonGeneratePoints;
    TButton* ButtonClear;
    TCheckBox* CheckBoxProcedure;
    void __fastcall ButtonConvexHullClick(TObject* Sender);
    void __fastcall ButtonGeneratePointsClick(TObject* Sender);
    void __fastcall ButtonClearClick(TObject* Sender);
    void __fastcall CheckBoxProcedureClick(TObject* Sender);
    void __fastcall ImageMouseDown(
        TObject* Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
  private: // User declarations
  public: // User declarations
    __fastcall TApp(TComponent* Owner);
};

vector<MyPoint> points;
stack<Graphics::TBitmap*> images;
MyPoint currentPoint;

bool operator<(const MyPoint &, const MyPoint &);

vector<MyPoint> MergeHulls(vector<MyPoint>, vector<MyPoint>);
vector<MyPoint> DivideAndConquerHull(vector<MyPoint>);

void DrawPolygon(vector<MyPoint>, TCanvas*, TColor);
void refresh();

//---------------------------------------------------------------------------
extern PACKAGE TApp* App;
//---------------------------------------------------------------------------
#endif

