#include "animationthread.h"
#include "algorithm.h"

AnimationThread::AnimationThread(Algorithm *algorithm)
    : QThread{}
    , _algorithm(algorithm)
{}

void AnimationThread::run()
{
    if (_algorithm) {
        _algorithm->run();
    }
}
