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

using namespace std;

TCanvas* canvas = 0;
Graphics::TBitmap* Empty = new Graphics::TBitmap();
Graphics::TBitmap* Image = new Graphics::TBitmap();

bool demo = false;

//---------------------------------------------------------------------------
class TApp : public TForm
{
  __published: // IDE-managed Components
    TMainMenu* MainMenu;
    TImage* Image;
    TButton* ButtonConvexHull;
    TButton* ButtonGeneratePoints;
    TButton* ButtonClear;
    TCheckBox* CheckBoxProcedure;
    void __fastcall ImageClick(TObject* Sender);
    void __fastcall ButtonConvexHullClick(TObject* Sender);
    void __fastcall ButtonGeneratePointsClick(TObject* Sender);
    void __fastcall ButtonClearClick(TObject* Sender);
    void __fastcall CheckBoxProcedureClick(TObject* Sender);
  private: // User declarations
  public: // User declarations
    __fastcall TApp(TComponent* Owner);
};

void refresh;

vector<MyPoint> points;
stack<Graphics::TBitmap *> images;
MyPoint currentPoint;

//---------------------------------------------------------------------------
extern PACKAGE TApp* App;
//---------------------------------------------------------------------------
#endif

