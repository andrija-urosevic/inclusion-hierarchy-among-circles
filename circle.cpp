#include "circle.h"
#include "myalgorithm.h"

#include <cmath>

Circle::Circle()
    : _center(0, 0)
    , _radius(0)
    , _inclusion(nullptr)
    , _left_extreme(nullptr)
    , _right_extreme(nullptr)
{}

Circle::Circle(QPoint center, int radius)
    : _center(center)
    , _radius(radius)
    , _inclusion(nullptr)
    , _left_extreme(nullptr)
    , _right_extreme(nullptr)
{
}

void Circle::draw(QPainter &painter) const
{
    QPen pen = painter.pen();

    pen.setColor(Qt::black);
    pen.setWidth(5);
    painter.setPen(pen);

    painter.drawPoint(_center);
    painter.drawEllipse(_center, _radius, _radius);

    pen.setColor(Qt::red);
    pen.setWidth(2);
    painter.setPen(pen);

    if (_inclusion != nullptr) {
        painter.drawLine(_center, _inclusion->center());
    }

}

double Circle::distanceSquare(const Circle &other) const
{
    return (_center.x() - other._center.x()) * (_center.x() - other._center.x())
         + (_center.y() - other._center.y()) * (_center.y() - other._center.y());
}

double Circle::distance(const Circle &other) const
{
    return std::sqrt(distanceSquare(other));
}

bool Circle::includes(const Circle &other) const
{
    const auto dist = distance(other);
    return !(dist >= _radius + other._radius) // overlapping
        && (dist <= _radius - other._radius); // this includes other
}

bool Circle::intersects(const Circle &other) const
{
    const auto dist = distance(other);

    return !(dist >= _radius + other._radius) // overlapping
           && !(dist <= std::abs(_radius - other._radius)); // non-inclusion
}

void Circle::setLeftExtreme(EventPtr left)
{
    _left_extreme = left;
}

void Circle::setRigthExtreme(EventPtr right)
{
    _right_extreme = right;
}

QPoint Circle::center() const
{
    return _center;
}

int Circle::radius() const
{
    return _radius;
}

EventPtr Circle::left_extreme() const
{
    return _left_extreme;
}

EventPtr Circle::right_extreme() const
{
    return _right_extreme;
}

double Circle::upper_value() const
{
    int b = - 2 * _center.y();
    int c = _center.y() * _center.y() +
            (MyAlgorithm::SweepLineX - _center.x()) * (MyAlgorithm::SweepLineX - _center.x()) -
            _radius * _radius;
    int delta = b * b - 4 * c;
    return (-b + sqrt(delta)) / 2;
}

double Circle::lower_value() const
{
    int b = - 2 * _center.y();
    int c = _center.y() * _center.y() +
            (MyAlgorithm::SweepLineX - _center.x()) * (MyAlgorithm::SweepLineX - _center.x()) -
            _radius * _radius;
    int delta = b * b - 4 * c;
    return (-b - sqrt(delta)) / 2;
}

void Circle::setInclusion(CirclePtr other)
{
    _inclusion = other;
}

CirclePtr Circle::inclusion()
{
    return _inclusion;
}
