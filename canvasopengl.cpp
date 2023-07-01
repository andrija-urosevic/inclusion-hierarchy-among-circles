#include "canvasopengl.h"
#include <GL/glut.h>

CanvasOpenGL::CanvasOpenGL(QWidget* parent)
    : QOpenGLWidget(parent)
    , _algorithm(nullptr)
    , _clear(false)
{
    xRot = 0;
    yRot = 0;
    zRot = 0;
}

void CanvasOpenGL::initializeGL()
{
    glClearColor(0.2,0.2,0.2,0);
    glEnable(GL_DEPTH_TEST);
    glPointSize(5);
}

void CanvasOpenGL::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(1, 2, 3, 0, 0, 0, 0, 1, 0);

    glRotatef(xRot, 1.0, 0.0, 0.0);
    glRotatef(yRot, 0.0, 1.0, 0.0);
    glRotatef(zRot, 0.0, 0.0, 1.0);

    if (_clear == false) {
        if (_algorithm) {
            _algorithm->draw3D();
        }
    } else {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
}

void CanvasOpenGL::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (float)w/h, 0.01, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(1,2,3,0,0,0,0,1,0);
}

void CanvasOpenGL::setAlgorithm(Algorithm *algorithm)
{
    _algorithm = algorithm;
}

void CanvasOpenGL::setClear(bool clear)
{
    _clear = clear;
}

void CanvasOpenGL::setXRotation(int angle)
{
    if (angle != xRot) {
       xRot = angle;
       update();
    }
}

void CanvasOpenGL::setYRotation(int angle)
{
    if (angle != yRot) {
        yRot = angle;
        update();
    }
}

void CanvasOpenGL::setZRotation(int angle)
{
    if (angle != zRot) {
        zRot = angle;
        update();
    }
}

void CanvasOpenGL::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void CanvasOpenGL::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        setXRotation(xRot + dy);
        setYRotation(yRot + dx);
    } else if (event->buttons() & Qt::RightButton) {
        setXRotation(xRot + dy);
        setZRotation(zRot + dx);
    }
    lastPos = event->pos();
}
