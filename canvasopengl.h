#ifndef CANVASOPENGL_H
#define CANVASOPENGL_H

#include <QOpenGLWidget>
#include <QMouseEvent>

#include "algorithm.h"

class CanvasOpenGL : public QOpenGLWidget
{
     Q_OBJECT
public:
    explicit CanvasOpenGL(QWidget* parent = 0);

    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;

    void setAlgorithm(Algorithm *algorithm);
    void setClear(bool clear);

    /* rotation with mouse */
    QPoint lastPos;
    int xRot;
    int yRot;
    int zRot;

    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);

    void mousePressEvent(QMouseEvent * event) override;
    void mouseMoveEvent(QMouseEvent * event) override;

private:
    Algorithm *_algorithm;
    bool _clear;
};

#endif // CANVASOPENGL_H
