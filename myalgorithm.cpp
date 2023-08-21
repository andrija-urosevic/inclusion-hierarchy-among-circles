#include "myalgorithm.h"

#include <cmath>
#include <fstream>
#include <iostream>
#include <set>
#include <QPainter>

int MyAlgorithm::SweepLineX = 0;

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
   std::vector<EventPtr> events;

   for (auto &circle : _circles) {
        EventPtr left = std::make_shared<Event>(circle, true);
        EventPtr right = std::make_shared<Event>(circle, false);

        events.push_back(left);
        events.push_back(right);
   }

   std::sort(events.begin(), events.end(), [](auto event1, auto event2) {
       return event1->x() < event2->x();
   });

   std::set<Interval> intervals;

   CirclePtr inf_circle = std::make_shared<Circle>(QPoint(0, 0), 1e5);
   auto i0 = Interval(inf_circle);

   intervals.insert(i0);

   UPDATE_CANVAS_AND_BLOCK();

   for (auto &event : events) {
        SweepLineX = event->x();
        auto i2 = Interval(event->circle());
        if (event->opening()) {
            auto i1_it = std::prev(intervals.lower_bound(i2));
            auto i1 = *i1_it;
            intervals.erase(i1_it);

            if (i1.containing_circle() != inf_circle) {
                event->circle()->setInclusion(i1.containing_circle());
            }

            auto i3 = Interval(i1);

            i1.setLowerCircle(event->circle(), false);
            i3.setUpperCircle(event->circle(), false);

            intervals.insert(i1);
            intervals.insert(i2);
            intervals.insert(i3);
        } else {
            auto i2_it = intervals.lower_bound(i2);
            auto i1_it = std::prev(i2_it);
            auto i3_it = std::next(i2_it);

            auto i1 = *i1_it;

            i1.setUpperCircle(i3_it->upper_circle(), i3_it->upper_side());

            intervals.erase(i1_it);
            intervals.erase(i3_it);
            intervals.erase(i2_it);

            intervals.insert(i1);
        }
        UPDATE_CANVAS_AND_BLOCK();
    }
}

void MyAlgorithm::draw(QPainter &painter) const
{
    QPen pen = painter.pen();
    pen.setColor(Qt::blue);
    pen.setWidth(5);;

    pen.setCapStyle(Qt::RoundCap);
    painter.setPen(pen);

    painter.drawLine(QPoint(MyAlgorithm::SweepLineX, 0), QPoint(MyAlgorithm::SweepLineX, 1000));

    for (auto &circle : _circles) {
        circle->draw(painter);
    }
}

void MyAlgorithm::draw3D() const
{

}

void MyAlgorithm::runNaive()
{
    for (size_t i = 0; i < _circles.size(); ++i) {
        for (size_t j = 0; j < _circles.size(); ++j) {
            if (i != j && _circles[i]->includes(*_circles[j])) {
                _circles[j]->setInclusion(_circles[i]);
            }
        }
    }
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

    x_max = 10000;
    y_max = 10000;
    x_min = -10000;
    y_min = -10000;

    int x_diff = x_max - x_min;
    int y_diff = y_max - y_min;

    srand(static_cast<unsigned>(1042));

    for (int i = 0; i <= num_circles; ++i) {
        CirclePtr circle;
        do {
            QPoint point{ x_min + rand() % x_diff, y_min + rand() % y_diff };
            circle = std::make_shared<Circle>(point, RAND_RANGE(Circle::MIN_RADIUS, Circle::MAX_RADIUS));
        } while (intersects(circle));

        _circles.push_back(circle);
    }
}

void MyAlgorithm::load_circles(std::string filename)
{
    int x, y, radius;
    std::ifstream input(filename);

    while(input >> x >> y >> radius)
        _circles.push_back(std::make_shared<Circle>(QPoint(x, y), radius));
}

bool MyAlgorithm::intersects(CirclePtr circle) const
{
    return std::any_of(_circles.begin(), _circles.end(), [circle] (auto other) {
        return circle->intersects(*other);
    });
}

