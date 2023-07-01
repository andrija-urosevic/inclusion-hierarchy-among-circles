#ifndef TIMEMEASUREMENTTHREAD_H
#define TIMEMEASUREMENTTHREAD_H

#include <QThread>

#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>

class TimeMeasurementThread : public QThread
{
    Q_OBJECT

public:
    TimeMeasurementThread(QString algorithm_type, int min_value, int step, int max_value);

    void run();

signals:
    void updateChart(double dim, double optimal, double naive);

private:
    QString _algorithm_type;
    int _min_value;
    int _step;
    int _max_value;
};

#endif // TIMEMEASUREMENTTHREAD_H
