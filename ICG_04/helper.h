//---------------------------------------------------------------------------

#ifndef HelperH
#define HelperH

#include <MyPoint.h>
#include <set>

using namespace std;

int AreaPoly2(int, const MyPoint[100]);
bool XOR(bool, bool);
int remainder(int, int);
bool firstSubsetofSecond(int[3], int[3]);

bool Diagonal_IE(int, int, int, MyPoint[100]);
bool Diagonal(int, int, int, MyPoint[100]);
bool InCone(int, int, int, MyPoint[100]);
void ClipEar(int, int, MyPoint[100]);
int remainder(int, int);
bool firstSubsetofSecond(int a[3], int b[3]);

int missingElement(int[10], int[10]);
void endpoints(MyDiagonal, int[2], int[3]);
/*
int clear();
void no_name2(int, MyPoint[500]);
*/

//---------------------------------------------------------------------------
#endif

