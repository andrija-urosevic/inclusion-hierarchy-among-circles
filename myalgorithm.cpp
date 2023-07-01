#include "myalgorithm.h"

#include <QPainter>

MyAlgorithm::MyAlgorithm(QWidget* canvas, QOpenGLWidget* canvas3D, int pause_length,
                         std::string filename, int num_points)
    : Algorithm(canvas, canvas3D, pause_length)
{
    if (filename == "") {
        _points = generateRandomPoints(num_points);
    } else {
        _points = loadData(filename);
    }
}

void MyAlgorithm::run()
{
    for (auto &point : _points) {
        _points_to_draw.push_back(point);
        UPDATE_CANVAS_AND_BLOCK();
    }

    UPDATE_CANVAS_AND_BLOCK();
    emit animationEnded();
}

void MyAlgorithm::draw(QPainter &painter) const
{
    QPen pen = painter.pen();
    pen.setColor(Qt::black);
    pen.setWidth(5);
    pen.setCapStyle(Qt::RoundCap);
    painter.setPen(pen);

    for (auto &point : _points_to_draw) {
      painter.drawPoint(point);
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
