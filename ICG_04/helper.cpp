//---------------------------------------------------------------------------

#pragma hdrstop

#include "Helper.h"

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


/*
int complement(int[10], int[10]);
void no_name(MyDiagonal, int[2], int[3]);
int clear();
void no_name2(int, MyPoint[500]);
*/

//---------------------------------------------------------------------------
#pragma package(smart_init)

