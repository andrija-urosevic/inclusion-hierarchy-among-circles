#include "event.h"

#include "circle.h"

Event::Event(CirclePtr circle, bool opening)
    : _circle(circle)
    , _opening(opening)
{
    if (opening)
        _x = circle->center().x() - circle->radius();
    else
        _x = circle->center().x() + circle->radius();
}

CirclePtr Event::circle() const
{
    return _circle;
}

bool Event::opening() const
{
    return _opening;
}

int Event::x() const
{
    return _x;
}
