#ifndef EVENT_H
#define EVENT_H

#include <memory>

class Circle;

using CirclePtr = std::shared_ptr<Circle>;

class Event
{
public:
    Event(CirclePtr circle, bool opening);

    CirclePtr circle() const;
    bool opening() const;
    int x() const;

private:
    CirclePtr _circle;
    bool _opening;
    int _x;
};

#endif // EVENT_H
