//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "window.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TApp* App;

bool operator<(const MyPoint &a, const MyPoint &b)
{
    return ccw(currentPoint, a, b) == 1 ||
           (ccw(currentPoint, a, b) == 0 &&
               abs(currentPoint.x - a.x) < abs(currentPoint.x - b.x));
}

void DrawPolygon(vector<MyPoint> points, TCanvas* canvas, TColor color)
{
    canvas->Pen->Color = color;
    canvas->MoveTo(points[0].x, points[0].y);

    for (int i = 1; i < points.size(); i++)
        canvas->LineTo(points[i].x, points[i].y);

    canvas->LineTo(points[0].x, points[0].y);
    canvas->Pen->Color = clBlack;
}

vector<MyPoint> MergeHulls(vector<MyPoint> hullA, vector<MyPoint> hullB)
{
    vector<MyPoint> mergedHull;
    if (hullA.empty())
        return hullB;
    if (hullB.empty())
        return hullA;

    stable_sort(hullA.begin(), hullA.end(), comparePoints);
    stable_sort(hullB.begin(), hullB.end(), comparePoints);

    int indexA = hullA.size() - 1, indexB = 0;
    int upperA, lowerA, upperB, lowerB, nextA, nextB;

    currentPoint = hullA[hullA.size() - 1]; // Rightmost point in hullA
    stable_sort(hullA.begin(), hullA.end() - 1);
    currentPoint = hullB[0];
    stable_sort(hullB.begin() + 1, hullB.end());

    nextA = (indexA == hullA.size() - 1) ? 0 : indexA + 1;
    nextB = (indexB == 0) ? hullB.size() - 1 : indexB - 1;

    while (ccw(hullB[indexB], hullA[indexA], hullA[nextA]) == -1 ||
           ccw(hullA[indexA], hullB[indexB], hullB[nextB]) == 1)
    {
        if (ccw(hullB[indexB], hullA[indexA], hullA[nextA]) == -1)
            indexA = nextA;
        else
            indexB = nextB;

        nextA = (indexA == hullA.size() - 1) ? 0 : indexA + 1;
        nextB = (indexB == 0) ? hullB.size() - 1 : indexB - 1;
    }

    if (procedure == true) {
        canvas->MoveTo(hullA[indexA].x, hullA[indexA].y);
        canvas->LineTo(hullB[indexB].x, hullB[indexB].y);
        MessageDlgPos(
            "Lower Tangent", mtCustom, TMsgDlgButtons() << mbOK, 0, 800, 500);
    }

    upperA = indexA;
    upperB = indexB;

    indexA = hullA.size() - 1;
    indexB = 0;

    nextB = (indexB == hullB.size() - 1) ? 0 : indexB + 1;
    nextA = (indexA == 0) ? hullA.size() - 1 : indexA - 1;

    while (ccw(hullB[indexB], hullA[indexA], hullA[nextA]) == 1 ||
           ccw(hullA[indexA], hullB[indexB], hullB[nextB]) == -1)
    {
        if (ccw(hullB[indexB], hullA[indexA], hullA[nextA]) == 1)
            indexA = nextA;
        else
            indexB = nextB;

        nextB = (indexB == hullB.size() - 1) ? 0 : indexB + 1;
        nextA = (indexA == 0) ? hullA.size() - 1 : indexA - 1;
    }

    if (procedure == true) {
        canvas->MoveTo(hullA[indexA].x, hullA[indexA].y);
        canvas->LineTo(hullB[indexB].x, hullB[indexB].y);
        MessageDlgPos(
            "Upper tangent", mtCustom, TMsgDlgButtons() << mbOK, 0, 800, 500);
    }

    lowerA = indexA;
    lowerB = indexB;

    if (upperA > lowerA) {
        for (int i = upperA; i < hullA.size(); i++)
            mergedHull.push_back(hullA[i]);
        for (int i = 0; i <= lowerA; i++)
            mergedHull.push_back(hullA[i]);
    } else {
        for (int i = upperA; i <= lowerA; i++)
            mergedHull.push_back(hullA[i]);
    }

    if (lowerB > upperB) {
        for (int j = lowerB; j < hullB.size(); j++)
            mergedHull.push_back(hullB[j]);
        for (int j = 0; j <= upperB; j++)
            mergedHull.push_back(hullB[j]);
    } else {
        for (int j = lowerB; j <= upperB; j++)
            mergedHull.push_back(hullB[j]);
    }

    if (procedure == true) {
        App->Image->Picture->Bitmap->Assign(images.top());
        DrawPolygon(mergedHull, canvas, clRed);
        MessageDlgPos("The final CH obtained by merging", mtCustom,
            TMsgDlgButtons() << mbOK, 0, 800, 500);
    }

    return mergedHull;
}

vector<MyPoint> DivideAndConquerHull(vector<MyPoint> points)
{
    stable_sort(points.begin(), points.end(), comparePoints);
    vector<MyPoint> hull;
    int numPoints = points.size();

    if (numPoints <= 3) {
        for (int i = 0; i < numPoints; i++)
            hull.push_back(points[i]);

        if (procedure == true) {
            DrawPolygon(hull, canvas, clBlue);
            MessageDlgPos("Trivial Convex Hull (<=3 points)", mtCustom,
                TMsgDlgButtons() << mbOK, 0, 800, 500);
        }
    }

    if (numPoints > 3) {
        vector<MyPoint> leftPoints(
            points.begin(), points.begin() + (numPoints + 1) / 2);
        vector<MyPoint> rightPoints(
            points.begin() + (numPoints + 1) / 2, points.end());

        Graphics::TBitmap* newImage = new Graphics::TBitmap();
        newImage->Assign(App->Image->Picture->Graphic);

        vector<MyPoint> leftHull = DivideAndConquerHull(leftPoints);
        vector<MyPoint> rightHull = DivideAndConquerHull(rightPoints);

        images.push(newImage);
        hull = MergeHulls(leftHull, rightHull);
    }

    return hull;
}

void refresh()
{
    App->Image->Picture->Bitmap->Assign(Empty);
    canvas->Brush->Color = clGray;
    for (int i = 0; i < points.size(); i++)
        canvas->Ellipse(
            points[i].x - 2, points[i].y - 2, points[i].x + 2, points[i].y + 2);
}

//---------------------------------------------------------------------------
__fastcall TApp::TApp(TComponent* Owner) : TForm(Owner)
{
    canvas = Image->Canvas;
    Empty->Assign(Image->Picture->Graphic);
}

//---------------------------------------------------------------------------
void __fastcall TApp::ButtonConvexHullClick(TObject* Sender)
{
    refresh();
    vector<MyPoint> CH = DivideAndConquerHull(points);

    canvas->Pen->Width = 2;
    DrawPolygon(CH, canvas, clGreen);
    canvas->Pen->Width = 1;

    if (procedure == true) {
        MessageDlgPos(
            "Convex Hull!", mtCustom, TMsgDlgButtons() << mbOK, 0, 800, 500);
        refresh();
        canvas->Pen->Width = 2;
        DrawPolygon(CH, canvas, clGreen);
        canvas->Pen->Width = 1;
    }
}
//---------------------------------------------------------------------------
void __fastcall TApp::ButtonGeneratePointsClick(TObject* Sender)
{
    srand(time(0));
    ButtonClearClick(this);
    int numPoints = 100;
    for (int i = 0; i < numPoints; i++) {
        int x = 4 + rand() % (Image->Width - 8);
        int y = 4 + rand() % (Image->Height - 8);
        points.push_back(MyPoint(x, y));
        canvas->Brush->Color = clGray;
        canvas->Ellipse(x - 2, y - 2, x + 2, y + 2);
    }
}
//---------------------------------------------------------------------------
void __fastcall TApp::ButtonClearClick(TObject* Sender)
{
    points.clear();
    App->Image->Picture->Bitmap->Assign(Empty);
}
//---------------------------------------------------------------------------
void __fastcall TApp::CheckBoxProcedureClick(TObject* Sender)
{
    procedure = CheckBoxProcedure->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TApp::ImageMouseDown(
    TObject* Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    canvas->Brush->Color = clGray;
    canvas->Ellipse(X - 2, Y - 2, X + 2, Y + 2);
    points.push_back(MyPoint(X, Y));
}
//---------------------------------------------------------------------------

