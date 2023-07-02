#ifndef CIRCLE_H
#define CIRCLE_H

#include <QPoint>
#include <QPainter>

class Circle
{
public:
    static int constexpr MIN_RADIUS = 20;
    static int constexpr MAX_RADIUS = 200;

public:
    Circle();
    Circle(QPoint point, int radius);

    void draw(QPainter &painter) const;

    double distanceSquare(const Circle &other) const;
    double distance(const Circle &other) const;
    bool intersects(const Circle &other) const;

    QPoint point() const;
    int radius() const;
    int left_extreme() const;
    int right_extreme() const;

private:
    QPoint _point;
    int _radius;

    int _left_extreme;
    int _right_extreme;
};

#endif // CIRCLE_H
