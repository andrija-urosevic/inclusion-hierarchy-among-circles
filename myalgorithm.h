#ifndef MYALGORITHM_H
#define MYALGORITHM_H

#include "algorithm.h"


#define RAND_RANGE(a, b) (rand() % ((b)- (a) + 1) + (a))

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
