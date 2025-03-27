//---------------------------------------------------------------------------

#ifndef WindowH
#define WindowH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <MyPoint.h>
#include <list>
#include <stack>
//---------------------------------------------------------------------------
class TGrahamScan : public TForm
{
__published:	// IDE-managed Components
    TImage *Image;
    TButton *GeneratePointsButton;
    TButton *ClearButton;
    TButton *GrahamScanButton;
    TEdit *Edit;
    void __fastcall FormActivate(TObject *Sender);
    void __fastcall ImageMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
    void __fastcall GeneratePointsButtonClick(TObject *Sender);
    void __fastcall ClearButtonClick(TObject *Sender);
    void __fastcall GrahamScanButtonClick(TObject *Sender);
private:	// User declarations
list<MyPoint> GrahamScan(list<MyPoint>);
public:		// User declarations
    __fastcall TGrahamScan(TComponent* Owner);

    list<MyPoint> pointList;
};
//---------------------------------------------------------------------------
extern PACKAGE TGrahamScan *GrahamScan;
//---------------------------------------------------------------------------
#endif
