#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "algorithm.h"
#include "canvas.h"
#include "canvasopengl.h"
#include "timemeasurementthread.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_filename_button_clicked();

    void on_random_button_clicked();

    void on_clear_button_clicked();

    void on_compare_button_clicked();

    void on_start_button_clicked();

    void on_pause_resume_button_clicked();

    void on_next_button_clicked();

    void on_restart_button_clicked();

    void on_line_series_change(double dim, double optimal, double naive);

    void on_algorithm_type_currentIndexChanged(int index);

public slots:
    void on_animation_end();

private:
    void animation_button_active(bool param);

    void animation_parameter_button_active(bool param);

    void make_new_algorithm();

private:
    Ui::MainWindow *ui;

    Algorithm *_algorithm;
    Canvas *_canvas;
    CanvasOpenGL *_canvas3D;
    std::string _filename;
    int _pause_length;
    int _number_of_random_points;
    bool _naive;

    QtCharts::QLineSeries *_naive_series;
    QtCharts::QLineSeries *_optimal_series;

    TimeMeasurementThread* _thread;
};
#endif // MAINWINDOW_H
