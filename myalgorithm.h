#ifndef MYALGORITHM_H
#define MYALGORITHM_H

#include "algorithm.h"

#define RAND_RANGE(a, b) (rand() % ((b)- (a) + 1) + (a))

class Circle
{
public:
    static int constexpr MIN_RADIUS = 20;
    static int constexpr MAX_RADIUS = 200;

public:
    Circle();
    Circle(QPoint _point, int _radius);

    void draw(QPainter &painter) const;

    double distanceSquare(const Circle &other) const;
    double distance(const Circle &other) const;
    bool intersects(const Circle &other) const;

    QPoint point;
    int radius;
};

class MyAlgorithm : public Algorithm
{
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

    bool intersects(const Circle &circle) const;

private:
    std::vector<Circle> _circles;
};

#endif // MYALGORITHM_H
