//---------------------------------------------------------------------------

#ifndef helperH
#define helperH

struct MyPoint {
	double x,y;
	MyPoint(double x, double y): x(x), y(y){}
	bool operator<(MyPoint);
    void Draw(TImage*, TColor = clBlack, int=3);
};

int Orientation(MyPoint, MyPoint, MyPoint);
//---------------------------------------------------------------------------
#endif
