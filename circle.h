#ifndef CIRCLE_H
#define CIRCLE_H

#include <QPoint>
#include <QPainter>

class Event;
class Circle;

using EventPtr = std::shared_ptr<Event>;
using CirclePtr = std::shared_ptr<Circle>;

class Circle
{
public:
    static int constexpr MIN_RADIUS = 20;
    static int constexpr MAX_RADIUS = 200;

public:
    Circle();
    Circle(QPoint center, int radius);

    void draw(QPainter &painter) const;

    double distanceSquare(const Circle &other) const;
    double distance(const Circle &other) const;
    bool includes(const Circle &other) const;
    bool intersects(const Circle &other) const;

    void setLeftExtreme(EventPtr left);
    void setRigthExtreme(EventPtr right);

    QPoint center() const;
    int radius() const;

    EventPtr left_extreme() const;
    EventPtr right_extreme() const;

    double upper_value() const;
    double lower_value() const;

    void setInclusion(CirclePtr other);
    CirclePtr inclusion();

private:
    QPoint _center;
    int _radius;

    CirclePtr _inclusion;

    EventPtr _left_extreme;
    EventPtr _right_extreme;
};

#endif // CIRCLE_H
