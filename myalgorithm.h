#ifndef MYALGORITHM_H
#define MYALGORITHM_H

#include "algorithm.h"

class MyAlgorithm : public Algorithm
{
public:
    MyAlgorithm(QWidget* canvas, QOpenGLWidget* canvas3D, int pause_length,
                std::string filename="", int num_points = 20);

    void run();
    void draw(QPainter &painter) const;
    void draw3D() const;
    void runNaive();
    bool is3D() const;

private:
    std::vector<QPoint> _points;
    std::vector<QPoint> _points_to_draw;
};

#endif // MYALGORITHM_H
