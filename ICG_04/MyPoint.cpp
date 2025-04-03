//---------------------------------------------------------------------------

#pragma hdrstop

#include "MyPoint.h"
#include <helper.h>

MyPoint &MyPoint::operator=(const MyPoint &other)
{
    // Check for self-assignment
    if (this != &other) {
        x = other.x;
        y = other.y;
        id = other.id;
    }
    return *this;
}

MyPoint MyPoint::operator-(const MyPoint &b) const
{
    MyPoint result;
    result.x = this->x - b.x;
    result.y = this->y - b.y;
    return result;
}

int MyPoint::Dot(const MyPoint &b) const
{
    return this->x * b.x + this->y * b.y;
}

int MyPoint::Length2() const
{
    return this->Dot(*this);
}

bool MyPoint::IsPointOnSegment(const MyPoint &a, const MyPoint &b) const
{
    MyPoint vector_ab = b - a;
    MyPoint vector_ac = *this - a;

    if (!Collinear(a, b, *this))
        return false;

    return vector_ab.Dot(vector_ac) >= 0 &&
           vector_ac.Length2() <= vector_ab.Length2();
}

// The area is positive if a,b,c are oriented ccw,
// negative if cw, and zero if the points are collinear.
int Area2(const MyPoint &a, const MyPoint &b, const MyPoint &c)
{
    return (a.x * b.y - b.x * a.y) + (b.x * c.y - c.x * b.y) +
           (c.x * a.y - a.x * c.y);
}

/*
	Returns true iff ab properly intersects cd: they share
	a point interior to both segments.  The properness of the
	intersection is ensured by using strict leftness.
*/
bool IntersectProp(
    const MyPoint &a, const MyPoint &b, const MyPoint &c, const MyPoint &d)
{
    return XOR(Left(a, b, c), Left(a, b, d)) &&
           XOR(Left(c, d, a), Left(c, d, b));
}

/*
	Returns true iff c is strictly to the left of the directed
	line through a to b.
*/
bool Left(const MyPoint &a, const MyPoint &b, const MyPoint &c)
{
    return Area2(a, b, c) > 0;
}

bool LeftOn(const MyPoint &a, const MyPoint &b, const MyPoint &c)
{
    return Area2(a, b, c) >= 0;
}

bool Collinear(const MyPoint &a, const MyPoint &b, const MyPoint &c)
{
    return Area2(a, b, c) == 0;
}

bool Intersect(
    const MyPoint &a, const MyPoint &b, const MyPoint &c, const MyPoint &d)
{
    if (IntersectProp(a, b, c, d))
        return true;
    else if (c.IsPointOnSegment(a, b) || d.IsPointOnSegment(a, b) ||
             a.IsPointOnSegment(c, d) || b.IsPointOnSegment(c, d))
        return true;
    else
        return false;
}

//---------------------------------------------------------------------------
#pragma package(smart_init)

