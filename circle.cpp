#include "circle.h"

#include <cmath>

Circle::Circle()
    : _point(0, 0)
    , _radius(0)
    , _left_extreme(0)
    , _right_extreme(0)
{}

Circle::Circle(QPoint point, int radius)
    : _point(point)
    , _radius(radius)
{
    _left_extreme = _point.x() - _radius;
    _right_extreme = _point.x() + _radius;
}

void Circle::draw(QPainter &painter) const
{
    painter.drawPoint(_point);
    painter.drawEllipse(_point, _radius, _radius);
}

double Circle::distanceSquare(const Circle &other) const
{
    return (_point.x() - other._point.x()) * (_point.x() - other._point.x())
         + (_point.y() - other._point.y()) * (_point.y() - other._point.y());
}

double Circle::distance(const Circle &other) const
{
    return std::sqrt(distanceSquare(other));
}

bool Circle::intersects(const Circle &other) const
{
    const auto dist = distance(other);

    return !(dist >= _radius + other._radius)
           && !(dist <= std::abs(_radius - other._radius));
}

QPoint Circle::point() const
{
    return _point;
}

int Circle::radius() const
{
    return _radius;
}

int Circle::left_extreme() const
{
    return _left_extreme;
}

int Circle::right_extreme() const
{
    return _right_extreme;
}
