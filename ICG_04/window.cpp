//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Window.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TTriangulation* Triangulation;

// Returns twice the area of the polygon.
int AreaPoly2(int n, const MyPoint poly[100])
{
    int sum(0);

    // It breaks the n-sided polygon into
    // (n - 2) triangles, all sharing the first vertex.
    for (int i = 1; i < n - 1; i++)
        sum += Area2(poly[0], poly[i], poly[i + 1]);

    return sum;
}

bool XOR(bool x, bool y)
{
    !x ^ !y;
}

int remainder(int a, int b)
{
    return a - (a / b) * b;
};

bool firstSubsetofSecond(int a[3], int b[3])
{
    set<int> bSet(b, b + 3);

    // Check if all elements of a[] exist in bSet
    for (int i = 0; i < 3; i++) {
        // If a[i] is not in bSet
        if (bSet.find(a[i]) == bSet.end())
            return false;
    }
    return true;
}

// (vi, vj) is a proper internal or external diagonal of a polygon
bool Diagonal_IE(int i, int j, int n, MyPoint poly[100])
{
    for (int k = 0; k < n; k++) {
        int k1 = (k + 1) % n;
        // skip edges incident to vi or vj
        bool incident = (k == i) || (k == j) || (k1 == i) || (k1 == j);
        if (!incident) {
            // Check if the diagonal intersects the edge (poly[k], poly[k1])
            if (Intersect(poly[i], poly[j], poly[k], poly[k1]))
                return false;
        }
    }
    return true;
}

/*
	the diagonal (i,j) is striclty internal to the
	polygon in the neighborhood of the i endpoint
*/
bool InCone(int i, int j, int n, MyPoint poly[100])
{
    int next = (i + 1) % n;
    int prev = (i - 1 + n) % n;

    // Check if poly[i] is a convex vertex
    bool isConvex = Left(poly[prev], poly[i], poly[next]);

    if (isConvex) {
        // the diagonal (i, j) should lie within the cone
        return Left(poly[i], poly[j], poly[prev]) &&
               Left(poly[j], poly[i], poly[next]);
    } else {
        // the diagonal (i, j) should lie outside the cone
        return !(Left(poly[i], poly[j], poly[next]) &&
                 Left(poly[j], poly[i], poly[prev]));
    }
}

// (vi,vj) a proper internal diagonal
bool Diagonal(int i, int j, int n, MyPoint poly[100])
{
    return InCone(i, j, n, poly) && Diagonal_IE(i, j, n, poly);
}

void ClipEar(int i, int n, MyPoint poly[100])
{
    for (int k = i; k < n - 1; k++)
        poly[k] = poly[k + 1];
}

//  find the first element in array a that is not present in array b
int missingElement(int a[10], int b[10])
{
    int elementNotContained;
    for (int i = 0; i < 3; i++) {
        elementNotContained = true;
        for (int j = 0; j < 2; j++) {
            if (a[i] == b[j])
                elementNotContained = false;
        }
        if (elementNotContained)
            return a[i];
    }

    return -1; // Return -1 if no element in 'a' is missing from 'b'
}

void endpoints(struct Diagonal diag, int thirdVertices[2], int earIndices[3])
{
    int diagonalPoints[] = { diag.x, diag.y };
    int earVertices[3]; // Holds vertices of a polygon ear
    int foundCount = 0; // Tracks how many matching ears were found

    for (int i = 0; i < numEars; i++) {
        ears[i].indexes(
            earVertices); // Populate with the vertices of the current ear

        if (firstSubsetofSecond(diagonalPoints, earVertices))
        { // Check if diagonal is part of the ear
            thirdVertices[foundCount] = missingElement(
                earVertices, diagonalPoints); // Find missing vertex
            earIndices[foundCount++] = i; // Store the index of this ear
        }
    }
}

void triangulate(int numVertices, MyPoint inputPolygon[500])
{
    int remainingVertices = numVertices;
    MyPoint polygon[500];

    // Copy the input polygon into a local working array
    for (int j = 0; j < remainingVertices; j++)
        polygon[j] = inputPolygon[j];

    // Start ear clipping from the third vertex
    for (int i = 2; remainingVertices > 3;) {
        if (i == 0)
            i += 2;

        // Try to clip ears (a triangle that is a valid diagonal)
        while (Diagonal(i - 2, i, remainingVertices, polygon) == TRUE) {
            // Add a new diagonal
            diagonals[numDiagonals++] =
                Diagonal(polygon[i].id, polygon[i - 2].id);

            // Save the triangle as a new edge
            ears[numEars++] = Ear(polygon[i - 2], polygon[i - 1], polygon[i]);

            // Color the new triangle/edge
            ears[numEars - 1].color(canvas);

            // Clip the ear (remove vertex i-1)
            ClipEar(i - 1, remainingVertices, polygon);
            remainingVertices--;
        }

        // Move to next set of three vertices, in a circular manner
        if (remainder(i, numVertices) == 0 && i > 0)
            i = remainder(i + 1, numVertices) + 2;
        else
            i = remainder(i + 1, numVertices);
    }

    // Add the final triangle
    ears[numEars++] = Ear(polygon[0], polygon[1], polygon[2]);
    Ear(polygon[0], polygon[1], polygon[2]).color(canvas);
}

int clear()
{
    int needsAnotherPass = 0;

    for (int i = 0; i < numDiagonals; i++) {
        int replacementVertices[2], intersectsCircle = 0, affectedEdges[3];
        endpoints(diagonals[i], replacementVertices, affectedEdges);

        int originalStart = diagonals[i].x;
        int originalEnd = diagonals[i].y;

        double slope1, slope2, intercept1, intercept2;
        double circleCenterX, circleCenterY, originalRadius, replacementRadius;
        double x1, x2, x3, y1, y2, y3, x4, y4;

        // Original diagonal endpoints
        x1 = polygon[diagonals[i].x].x;
        y1 = polygon[diagonals[i].x].y;
        x3 = polygon[diagonals[i].y].x;
        y3 = polygon[diagonals[i].y].y;

        // Replacement endpoints
        x2 = polygon[replacementVertices[0]].x;
        y2 = polygon[replacementVertices[0]].y;
        x4 = polygon[replacementVertices[1]].x;
        y4 = polygon[replacementVertices[1]].y;

        // Calculate perpendicular bisector slopes
        slope1 = (y2 - y1) != 0 ? -(x2 - x1) / (y2 - y1) : 0;
        slope2 = (y3 - y2) != 0 ? -(x3 - x2) / (y3 - y2) : 0;

        // Find intercepts of the perpendicular bisectors
        intercept1 = ((y1 + y2) / 2) - slope1 * ((x1 + x2) / 2);
        intercept2 = ((y3 + y2) / 2) - slope2 * ((x3 + x2) / 2);

        // Find circle center (intersection of the bisectors)
        circleCenterX = (intercept1 - intercept2) / (slope2 - slope1);
        circleCenterY = slope1 * circleCenterX + intercept1;

        // Radius from center to original point and new point
        originalRadius =
            sqrt(pow(circleCenterY - y1, 2) + pow(circleCenterX - x1, 2));
        replacementRadius =
            sqrt(pow(circleCenterY - y4, 2) + pow(circleCenterX - x4, 2));

        int shouldReplace = 0;

        // Optional drawing and visual feedback
        if (Triangulation->CheckBoxProcedure->Checked == true) {
            Triangulation->Image->Picture->Bitmap->Assign(bmp);
            canvas->Arc(circleCenterX - originalRadius,
                circleCenterY + originalRadius, circleCenterX + originalRadius,
                circleCenterY - originalRadius, circleCenterX + originalRadius,
                circleCenterY, circleCenterX + originalRadius, circleCenterY);
            ShowMessage("Next iteration");
            Triangulation->Image->Picture->Bitmap->Assign(bmp);
        }

        if (replacementRadius < originalRadius)
            intersectsCircle = 1;

        bool isValid = Diagonal(
            replacementVertices[1], replacementVertices[0], numPoints, polygon);
        if (isValid)
            shouldReplace = 1;

        if (intersectsCircle && shouldReplace) {
            // Replace the diagonal with a new one
            diagonals[i].x = replacementVertices[0];
            diagonals[i].y = replacementVertices[1];

            // Update affected edges
            ears[affectedEdges[0]] = Ear(polygon[replacementVertices[0]],
                polygon[replacementVertices[1]], polygon[originalStart]);
            ears[affectedEdges[1]] = Ear(polygon[replacementVertices[0]],
                polygon[replacementVertices[1]], polygon[originalEnd]);

            // Recolor the updated edges
            ears[affectedEdges[0]].color(canvas);
            ears[affectedEdges[1]].color(canvas);

            i--; // Recheck the new diagonal
            needsAnotherPass = 1;
        }

        if (Triangulation->CheckBoxProcedure->Checked == true)
            bmp->Assign(Triangulation->Image->Picture->Bitmap);
    }

    if (needsAnotherPass)
        clear(); // Recurse if any diagonals were replaced
}

//---------------------------------------------------------------------------

__fastcall TTriangulation::TTriangulation(TComponent* Owner) : TForm(Owner) {}

//---------------------------------------------------------------------------

TTriangulation::~TTriangulation()
{
    if (bmp) {
        delete bmp;
    }
    if (canvas) {
        delete canvas;
    }
}

//---------------------------------------------------------------------------
void __fastcall TTriangulation::ImageMouseDown(
    TObject* Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    MyPoint MyPoint1;
    if (numPoints == 0) {
        canvas->Pixels[X][Y] = clBlack;
        canvas->MoveTo(X, Y);
        MyPoint1.x = X;
        MyPoint1.y = Y;
        MyPoint1.id = numPoints;
        polygon[numPoints] = MyPoint1;
        numPoints++;
    } else {
        MyPoint1.x = X;
        MyPoint1.y = Y;
        MyPoint1.id = numPoints;
        polygon[numPoints] = MyPoint1;
        canvas->LineTo(polygon[numPoints].x, polygon[numPoints].y);
        numPoints++;
    };
}
//---------------------------------------------------------------------------

void __fastcall TTriangulation::ButtonTriangulationClick(TObject* Sender)
{
    int how_many;
    struct Diagonal array[500];
    triangulate(numPoints, polygon);
    canvas->MoveTo(polygon[0].x, polygon[0].y);
    canvas->LineTo(polygon[numPoints - 1].x, polygon[numPoints - 1].y);

    bmp->Assign(Image->Picture->Bitmap);
}
//---------------------------------------------------------------------------

void __fastcall TTriangulation::ButtonClearClick(TObject* Sender)
{
    canvas->Brush->Color = clWhite;
    canvas->FillRect(Image->ClientRect);
    numPoints = 0;
    numEars = 0;
    numDiagonals = 0;
}
//---------------------------------------------------------------------------

void __fastcall TTriangulation::ButtonImproveClick(TObject* Sender)
{
    clear();
}
//---------------------------------------------------------------------------

void __fastcall TTriangulation::FormCreate(TObject* Sender)
{
    canvas = Image->Canvas;
    canvas->Brush->Color = clWhite;
    canvas->FillRect(Image->ClientRect);
    numPoints = 0;
}
//---------------------------------------------------------------------------

