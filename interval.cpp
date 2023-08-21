#include "interval.h"
#include "circle.h"

#include <climits>

Interval::Interval(CirclePtr containing_circle)
    : _containing_circle(containing_circle)
    , _upper_circle(containing_circle)
    , _lower_circle(containing_circle)
    , _upper_side(true)
    , _lower_side(true)
{
}

double Interval::upper_value() const
{
    if (_upper_side) {
        return _upper_circle->upper_value();
    }

    return _upper_circle->lower_value();
}

double Interval::lower_value() const
{
    if (_lower_side) {
        return _lower_circle->lower_value();
    }

    return _lower_circle->upper_value();
}

CirclePtr Interval::containing_circle() const
{
    return _containing_circle;
}

void Interval::setContainingCircle(CirclePtr containing_circle)
{
    _upper_circle = containing_circle;
    _containing_circle = containing_circle;
    _lower_circle = containing_circle;
    _upper_side = true;
    _lower_side = true;
}

CirclePtr Interval::upper_circle() const
{
    return _upper_circle;
}

void Interval::setUpperCircle(CirclePtr upper_circle, bool upper_side)
{
    _upper_circle = upper_circle;
    _upper_side = upper_side;
}

CirclePtr Interval::lower_circle() const
{
    return _lower_circle;
}

void Interval::setLowerCircle(CirclePtr lower_circle, bool lower_side)
{
    _lower_circle = lower_circle;
    _lower_side = lower_side;
}

bool Interval::operator<(const Interval &other) const
{
    return lower_value() + EPS < other.lower_value()
        || upper_value() + EPS < other.upper_value();
}

bool Interval::operator==(const Interval &other) const
{
    return !(*this < other) && !(other < *this);
}

bool Interval::upper_side() const
{
    return _upper_side;
}

bool Interval::lower_side() const
{
    return _lower_side;
}
