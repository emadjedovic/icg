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
//---------------------------------------------------------------------------
class TGrahamScan : public TForm
{
__published:	// IDE-managed Components
    TImage *Image;
    TButton *GeneratePoints;
    TButton *Clear;
    TButton *GrahamScan;
    TEdit *Edit;
    void __fastcall FormActivate(TObject *Sender);
    void __fastcall ImageMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
    void __fastcall GeneratePointsClick(TObject *Sender);
    void __fastcall ClearClick(TObject *Sender);
    void __fastcall GrahamScanClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TGrahamScan(TComponent* Owner);

    list<MyPoint> pointList;
};
//---------------------------------------------------------------------------
extern PACKAGE TGrahamScan *GrahamScan;
//---------------------------------------------------------------------------
#endif
