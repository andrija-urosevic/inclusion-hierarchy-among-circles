#include "algorithm.h"

#include <fstream>

Algorithm::Algorithm(QWidget *canvas, QOpenGLWidget *canvas3D, int pause_length)
    : QObject()
    , _canvas(canvas)
    , _canvas3D(canvas3D)
    , _pause_length(pause_length)
    , _timer_id(INVALID_TIMER_ID)
    , _semaphore(0)
    , _distroy_animation(false)
    , _thread(nullptr)
{}

void Algorithm::startAnimation()
{
    delete _thread;
    _thread = new AnimationThread(this);
    _thread->start();
    _timer_id = startTimer(_pause_length);
    _canvas->update();
    _canvas3D->update();
}

void Algorithm::pauseResumeAnimaiton()
{
    if (INVALID_TIMER_ID != _timer_id) {
        killTimer(_timer_id);
        _timer_id = INVALID_TIMER_ID;
    } else {
        _timer_id = startTimer(_pause_length);
    }
}

void Algorithm::nextAnimation()
{
    if (INVALID_TIMER_ID != _timer_id) {
        killTimer(_timer_id);
        _timer_id = INVALID_TIMER_ID;
    }

    _semaphore.release();
}

void Algorithm::stopAnimation()
{
    _distroy_animation = true;
    _semaphore.release();
    _thread->quit();
    _thread->wait();

    delete _thread;
    _thread = nullptr;
    _distroy_animation = false;
}

void Algorithm::setPauseLength(int pause_length)
{
    if (INVALID_TIMER_ID != _timer_id)
        killTimer(_timer_id);
    _pause_length = pause_length;
    _timer_id = startTimer(_pause_length);
}

bool Algorithm::updateCanvasAndBlock()
{
    if (_canvas) {
        _canvas->update();
        _canvas3D->update();
        _semaphore.acquire();
    }
    return _distroy_animation;
}

std::vector<QPoint> Algorithm::generateRandomPoints(int num_points)
{
    std::vector<QPoint> random_points;

    int x_max, y_max;

    int x_min = DRAWING_BORDER;
    int y_min = DRAWING_BORDER;

    if (_canvas) {
        x_max = _canvas->width() - DRAWING_BORDER;
        y_max = _canvas->height() - DRAWING_BORDER;
    } else {
        x_max = 1000; // TODO: Remove magic constant
        y_max = 1000; // TOOD: Remove magic constant
    }

    int x_diff = x_max - x_min;
    int y_diff = y_max - y_min;

    srand(static_cast<unsigned>(time(0)));

    for(int i = 0; i < num_points; i++)
        random_points.push_back(QPoint(x_min + rand() % x_diff, y_min + rand() % y_diff));

    return random_points;
}

std::vector<QPoint> Algorithm::loadData(std::string filename)
{
    int x, y;
    std::vector<QPoint> points;
    std::ifstream input(filename);

    while(input >> x >> y)
        points.emplace_back(x, y);

    return points;
}

void Algorithm::timerEvent(QTimerEvent */* unused */)
{
     _semaphore.release();
}
