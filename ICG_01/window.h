//---------------------------------------------------------------------------

#ifndef windowH
#define windowH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TMyApp : public TForm
{
__published:	// IDE-managed Components
	TImage *Image;
	TButton *SimplePath;
	TButton *ConvexHull;
	TButton *Clear;
	void __fastcall ImageMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y);
	void __fastcall SimplePathClick(TObject *Sender);
	void __fastcall ClearClick(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
    void __fastcall ConvexHullClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TMyApp(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMyApp *MyApp;
//---------------------------------------------------------------------------
#endif
