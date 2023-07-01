#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QtGui>

#include "algorithm.h"

class Canvas : public QWidget
{
    Q_OBJECT
public:
    explicit Canvas(QWidget *parent = nullptr);
    void setAlgorithm(Algorithm *algorithm);

    void setClear(bool clear);

protected:
    void paintEvent(QPaintEvent*) override;

private:
    Algorithm *_algorithm;
    bool _clear;
};

#endif // CANVAS_H
