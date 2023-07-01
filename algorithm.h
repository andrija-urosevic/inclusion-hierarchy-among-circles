#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <QObject>
#include <QSemaphore>
#include <QWidget>
#include <QOpenGLWidget>

#include "animationthread.h"

#define UPDATE_CANVAS_AND_BLOCK() if (updateCanvasAndBlock()) return;

class Algorithm : public QObject
    {
    Q_OBJECT
private:
    static int constexpr INVALID_TIMER_ID = -1;
    static int constexpr DRAWING_BORDER = 10;
    void timerEvent(QTimerEvent */* unused */);

public:
    Algorithm(QWidget* canvas, QOpenGLWidget *canvas3D, int pause_steps);

    virtual void run() = 0;
    virtual void draw(QPainter &painter) const = 0;
    virtual void draw3D() const = 0;
    virtual void runNaive() = 0;
    virtual bool is3D() const = 0;

    void startAnimation();
    void pauseResumeAnimaiton();
    void nextAnimation();
    void stopAnimation();

    void setPauseLength(int pause_length);

signals:
    void animationEnded();

protected:
    QWidget *_canvas;
    QOpenGLWidget *_canvas3D;

    bool updateCanvasAndBlock();

    std::vector<QPoint> generateRandomPoints(int num_points = 40); // TODO: Remove magic constant
    std::vector<QPoint> loadData(std::string filename);

private:
    int _pause_length;
    int _timer_id;
    QSemaphore _semaphore;
    bool _distroy_animation;

    AnimationThread *_thread;
};

#endif // ALGORITHM_H
