#ifndef MYALGORITHM_H
#define MYALGORITHM_H

#include <set>
#include "algorithm.h"
#include "circle.h"
#include "event.h"
#include "interval.h"

#define RAND_RANGE(a, b) (rand() % ((b)- (a) + 1) + (a))

using CirclePtr = std::shared_ptr<Circle>;
using EventPtr = std::shared_ptr<Event>;
using IntervalPtr = std::shared_ptr<Interval>;

class MyAlgorithm : public Algorithm
{
public:
    static int SweepLineX;

public:
    MyAlgorithm(QWidget* canvas, QOpenGLWidget* canvas3D, int pause_length,
                std::string filename="", int num_circles = 20);

    void run();
    void draw(QPainter &painter) const;
    void draw3D() const;
    void runNaive();
    bool is3D() const;

private:
    void generate_random_circles(int num_circles);
    void load_circles(std::string filename);

    bool intersects(const CirclePtr circle) const;

private:
    std::vector<CirclePtr> _circles;
    std::set<Interval> _intervals;
};

#endif // MYALGORITHM_H
