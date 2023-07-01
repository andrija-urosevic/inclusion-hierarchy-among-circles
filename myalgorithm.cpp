#include "myalgorithm.h"

#include <cmath>
#include <fstream>
#include <QPainter>

MyAlgorithm::MyAlgorithm(QWidget* canvas, QOpenGLWidget* canvas3D, int pause_length,
                         std::string filename, int num_circles)
    : Algorithm(canvas, canvas3D, pause_length)
{
    if (filename == "") {
        generate_random_circles(num_circles);

    } else {
        load_circles(filename);
   }
}

void MyAlgorithm::run()
{
}

void MyAlgorithm::draw(QPainter &painter) const
{
    QPen pen = painter.pen();
    pen.setColor(Qt::black);
    pen.setWidth(5);
    pen.setCapStyle(Qt::RoundCap);
    painter.setPen(pen);

    for (auto &circle : _circles) {
        circle.draw(painter);
    }
}

void MyAlgorithm::draw3D() const
{

}

void MyAlgorithm::runNaive()
{

}

bool MyAlgorithm::is3D() const
{
    return false;
}

void MyAlgorithm::generate_random_circles(int num_circles)
{
    int x_max, y_max;

    int x_min = Algorithm::DRAWING_BORDER;
    int y_min = Algorithm::DRAWING_BORDER;

    if (_canvas) {
        x_max = _canvas->width() - DRAWING_BORDER;
        y_max = _canvas->height() - DRAWING_BORDER;
    } else {
        x_max = 1000; // TODO: Remove magic constant
        y_max = 1000; // TOOD: Remove magic constant
    }

    int x_diff = x_max - x_min;
    int y_diff = y_max - y_min;

    for (int i = 0; i <= num_circles; ++i) {
        Circle circle;
        do {
            QPoint point{ x_min + rand() % x_diff, y_min + rand() % y_diff };
            circle = Circle(point, RAND_RANGE(Circle::MIN_RADIUS, Circle::MAX_RADIUS));
        } while (intersects(circle));

        _circles.push_back(circle);
    }
}

void MyAlgorithm::load_circles(std::string filename)
{
    int x, y, radius;
    std::ifstream input(filename);

    while(input >> x >> y >> radius)
        _circles.emplace_back(QPoint(x, y), radius);
}

bool MyAlgorithm::intersects(const Circle &circle) const
{
    return std::any_of(_circles.begin(), _circles.end(), [circle] (auto &other) {
        return circle.intersects(other);
    });
}

Circle::Circle()
    : point(0, 0)
    , radius(0)
{}

Circle::Circle(QPoint _point, int _radius)
    : point(_point)
    , radius(_radius)
{}

void Circle::draw(QPainter &painter) const
{
    painter.drawPoint(point);
    painter.drawEllipse(point, radius, radius);
}

double Circle::distanceSquare(const Circle &other) const
{
    return (point.x() - other.point.x()) * (point.x() - other.point.x())
         + (point.y() - other.point.y()) * (point.y() - other.point.y());
}

double Circle::distance(const Circle &other) const
{
    return std::sqrt(distanceSquare(other));
}

bool Circle::intersects(const Circle &other) const
{
    const auto dist = distance(other);

    return !(dist >= radius + other.radius)
        && !(dist <= std::abs(radius - other.radius));
}
