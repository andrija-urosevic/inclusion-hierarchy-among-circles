#ifndef ANIMATIONTHREAD_H
#define ANIMATIONTHREAD_H

#include <QThread>

class Algorithm;

class AnimationThread : public QThread
{
public:
    AnimationThread(Algorithm *algorithm);

    virtual void run();

private:
    Algorithm *_algorithm;
};


#endif // ANIMATIONTHREAD_H
