#ifndef INTERVAL_H
#define INTERVAL_H

#include <memory>

class Circle;

using CirclePtr = std::shared_ptr<Circle>;

class Interval;

class Interval
{
public:
    static double constexpr EPS = 1e-5;

public:
    Interval(CirclePtr containing_circle);

    double upper_value() const;
    double lower_value() const;

    CirclePtr containing_circle() const;
    void setContainingCircle(CirclePtr containing_circle);
    CirclePtr upper_circle() const;
    void setUpperCircle(CirclePtr upper_circle, bool upper_side);
    CirclePtr lower_circle() const;
    void setLowerCircle(CirclePtr lower_circle, bool lower_side);

    bool operator<(const Interval &other) const;
    bool operator==(const Interval &other) const;

    bool upper_side() const;
    bool lower_side() const;

private:
    CirclePtr _containing_circle;
    CirclePtr _upper_circle;
    CirclePtr _lower_circle;

    bool _upper_side;
    bool _lower_side;
};

#endif // INTERVAL_H
