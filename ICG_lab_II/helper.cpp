#include "pch.h"
#include "helper.h"

bool MyPoint::operator<(MyPoint p)
{
    if (x < p.x)
        return true;
    if (x > p.x)
        return false;
    return y < p.y;
}

bool MyPoint::operator==(MyPoint p)
{
    return x == p.x && y == p.y;
}
