#include "timemeasurementthread.h"
#include "algorithm.h"

#include "myalgorithm.h"


TimeMeasurementThread::TimeMeasurementThread(QString algorithm_type, int min_value, int step, int max_value)
    : QThread ()
    , _algorithm_type(algorithm_type)
    , _min_value(min_value)
    , _step(step)
    , _max_value(max_value)
{
}

void TimeMeasurementThread::run()
{
    clock_t begin, end;
    double optimal_time, naive_time;

    Algorithm* algorithm = nullptr;
    for(int i = _min_value; i <= _max_value; i += _step) {

        if (_algorithm_type == "MyAlgorithm")
            algorithm = new MyAlgorithm(nullptr, nullptr, 0, "", i);

        if (algorithm) {
#ifndef SKIP_OPTIMAL
            begin = clock();
            algorithm->run();
            end = clock();
            optimal_time = double(end - begin) / CLOCKS_PER_SEC;
#else
            optimal_time = 0;
#endif

#ifndef SKIP_NAIVE
            begin = clock();
            algorithm->runNaive();
            end = clock();
            naive_time = double(end - begin) / CLOCKS_PER_SEC;
#else
            naive_time = 0;
#endif
            emit updateChart(i, optimal_time, naive_time);
            delete algorithm;
            algorithm = nullptr;
        }
    }
}
