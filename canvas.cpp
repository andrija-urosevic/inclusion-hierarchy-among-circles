#include "canvas.h"

Canvas::Canvas(QWidget *parent)
    : QWidget(parent)
    , _algorithm(nullptr)
    , _clear(false)
{
    QPalette pallete = palette();
    pallete.setColor(QPalette::Window, Qt::white);
    setAutoFillBackground(true);
    setPalette(pallete);
}

void Canvas::setAlgorithm(Algorithm *algorithm)
{
    _algorithm = algorithm;
}

void Canvas::setClear(bool clear)
{
    _clear = clear;
}

void Canvas::paintEvent(QPaintEvent *)
{
    QPainter qpainter(this);

    qpainter.translate(this->rect().bottomLeft());
    qpainter.scale(1.0, -1.0);

    qpainter.setRenderHint(QPainter::Antialiasing, true);

    QPen pen = qpainter.pen();
    pen.setColor(Qt::black);
    pen.setWidth(5);
    pen.setCapStyle(Qt::RoundCap);

    qpainter.setPen(pen);

    if (_clear == false) {
        qpainter.drawRect(0, 0, width() - 1, height() - 1);

        if (_algorithm)
            _algorithm->draw(qpainter);
    } else {
        qpainter.eraseRect(0, 0, width() - 1, height() - 1);
    }
}
