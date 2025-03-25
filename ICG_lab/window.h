//---------------------------------------------------------------------------

#ifndef windowH
#define windowH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "helper.h"
#include <vector>

using namespace std;
//---------------------------------------------------------------------------
class TICG_app : public TForm
{
__published:	// IDE-managed Components
	TImage *Image;
	TButton *ButtonSimplePolygon;
	void __fastcall ImageMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall ButtonSimplePolygonClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TICG_app(TComponent* Owner);

	vector<MyPoint> points;
};
//---------------------------------------------------------------------------
extern PACKAGE TICG_app *ICG_app;
//---------------------------------------------------------------------------
#endif
