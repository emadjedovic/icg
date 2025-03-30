//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "window.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TApp* App;

void DrawPolygon(vector<MyPoint> points, TCanvas* canvas, TColor color)
{
    canvas->Pen->Color = color;
    canvas->MoveTo(points[0].x, points[0].y);

    for (int i = 1; i < points.size(); i++)
        canvas->LineTo(points[i].x, points[i].y);

    canvas->LineTo(points[0].x, points[0].y);
    canvas->Pen->Color = clBlack;
}

vector<MyPoint> MergeHulls(vector<MyPoint> setLeft, vector<MyPoint> setRight)
{
    vector<MyPoint> mergedHull;

    if (setLeft.empty())
        return setRight;
    if (setRight.empty())
        return setLeft;

    stable_sort(setLeft.begin(), setLeft.end(), comparePoints);
    stable_sort(setRight.begin(), setRight.end(), comparePoints);

    int rightmostLeftIndex = setLeft.size() - 1;
    int leftmostRightIndex = 0;

    // Find lower tangent
    pair<int, int> lowerTangent = FindLowerTangent(
        setLeft, setRight, rightmostLeftIndex, leftmostRightIndex);
    int lowerLeftIndex = lowerTangent.first;
    int lowerRightIndex = lowerTangent.second;

    // Find upper tangent
    pair<int, int> upperTangent = FindUpperTangent(
        setLeft, setRight, rightmostLeftIndex, leftmostRightIndex);
    int upperLeftIndex = upperTangent.first;
    int upperRightIndex = upperTangent.second;

    // Merge hull points between tangents
    AddHullPoints(setLeft, mergedHull, lowerLeftIndex, upperLeftIndex);
    AddHullPoints(setRight, mergedHull, upperRightIndex, lowerRightIndex);

    return mergedHull;
}

pair<int, int> FindLowerTangent(vector<MyPoint> &setLeft,
    vector<MyPoint> &setRight, int leftIndex, int rightIndex)
{
    int prevLeftIndex, nextRightIndex;

    do {
        // Move to the previous point in setLeft (clockwise)
        prevLeftIndex = (leftIndex == 0) ? setLeft.size() - 1 : leftIndex - 1;

        // Move to the next point in setRight (counterclockwise)
        nextRightIndex = (rightIndex + 1) % setRight.size();

        // If moving prevLeftIndex results in a lower tangent, update `leftIndex`
        if (ccw(setRight[rightIndex], setLeft[leftIndex],
                setLeft[prevLeftIndex]) == -1)
            leftIndex = prevLeftIndex;

        // If moving nextRightIndex results in a lower tangent, update `rightIndex`
        if (ccw(setLeft[leftIndex], setRight[rightIndex],
                setRight[nextRightIndex]) == 1)
            rightIndex = nextRightIndex;

    } while (ccw(setRight[rightIndex], setLeft[leftIndex],
                 setLeft[prevLeftIndex]) == -1 ||
             ccw(setLeft[leftIndex], setRight[rightIndex],
                 setRight[nextRightIndex]) == 1);

    return { leftIndex, rightIndex }; // Return final lower tangent points
}

pair<int, int> FindUpperTangent(vector<MyPoint> &setLeft,
    vector<MyPoint> &setRight, int leftIndex, int rightIndex)
{
    int nextLeftIndex, prevRightIndex;

    do {
        // Move to the next point in setLeft (counterclockwise)
        nextLeftIndex = (leftIndex + 1) % setLeft.size();

        // Move to the previous point in setRight (clockwise)
        prevRightIndex =
            (rightIndex == 0) ? setRight.size() - 1 : rightIndex - 1;

        // If moving nextLeftIndex results in an upper tangent, update `leftIndex`
        if (ccw(setRight[rightIndex], setLeft[leftIndex],
                setLeft[nextLeftIndex]) == 1)
            leftIndex = nextLeftIndex;

        // If moving prevRightIndex results in an upper tangent, update `rightIndex`
        if (ccw(setLeft[leftIndex], setRight[rightIndex],
                setRight[prevRightIndex]) == -1)
            rightIndex = prevRightIndex;

    } while (ccw(setRight[rightIndex], setLeft[leftIndex],
                 setLeft[nextLeftIndex]) == 1 ||
             ccw(setLeft[leftIndex], setRight[rightIndex],
                 setRight[prevRightIndex]) == -1);

    return { leftIndex, rightIndex }; // Return final upper tangent points
}

void AddHullPoints(vector<MyPoint> &hull, vector<MyPoint> &mergedHull,
    int startIndex, int endIndex)
{
    int hullSize = hull.size();

    if (startIndex > endIndex) {
        for (int i = startIndex; i < hullSize; i++)
            mergedHull.push_back(hull[i]);

        for (int i = 0; i <= endIndex; i++)
            mergedHull.push_back(hull[i]);
    } else {
        // Add points sequentially from `startIndex` to `endIndex`
        for (int i = startIndex; i <= endIndex; i++)
            mergedHull.push_back(hull[i]);
    }
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

