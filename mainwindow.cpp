#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "myalgorithm.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , _filename("")
    , _pause_length(500) // TODO: Remove magic constant
    , _number_of_random_points(20) // TODO: Remove magic constant
    , _naive(false)
{
    ui->setupUi(this);
    ui->algorithm_type->insertSeparator(3);
    animation_button_active(false);
    animation_parameter_button_active(true);

    _canvas3D = ui->openGLWidget;

    _canvas = new Canvas(this);
    QBoxLayout *canvas_layout = new QBoxLayout(QBoxLayout::LeftToRight);
    canvas_layout->addWidget(_canvas);
    ui->tab->setLayout(canvas_layout);

    ui->num_points_text->setPlaceholderText("Uneti broj nasumicnih tacaka, podrazumevana vrednost je 20.");

    _optimal_series = new QtCharts::QLineSeries();
    _naive_series = new QtCharts::QLineSeries();

    QtCharts::QChart *chart = new QtCharts::QChart();
    _optimal_series->append(0,0);
    _naive_series->append(0,0);

    _optimal_series->setName("Optimalni algoritam");
    _naive_series->setName("Naivni algoritam");

    chart->addSeries(_optimal_series);
    chart->addSeries(_naive_series);

    chart->legend()->show();

    chart->createDefaultAxes();
    chart->setTitle("Poredjenje efikasnosti");

    chart->axes(Qt::Horizontal).constLast()->setRange(0, 1200); // TODO: Manage magic constant
    chart->axes(Qt::Vertical).constLast()->setRange(0, 0.02); // TODO: Manage magic constant

    chart->setBackgroundVisible(false);
    chart->setPlotAreaBackgroundVisible(true);

    QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QBoxLayout* chartBoxLayout = new QBoxLayout(QBoxLayout::LeftToRight);
    chartBoxLayout->addWidget(chartView);

    ui->tab_2->setLayout(chartBoxLayout);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::animation_button_active(bool param)
{
    ui->restart_button->setEnabled(param);
    ui->next_button->setEnabled(param);
    ui->pause_resume_button->setEnabled(param);
    ui->start_button->setEnabled(param);
    ui->compare_button->setEnabled(param);
}

void MainWindow::animation_parameter_button_active(bool param)
{
    ui->filename_button->setEnabled(!param);
    ui->clear_button->setEnabled(param);
    ui->algorithm_type->setEnabled(param);
    ui->random_button->setEnabled(!param);
}

void MainWindow::on_filename_button_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Datoteka sa koordinatama tacaka"), "./ulazni_podaci/", "*.*");
    if (filename.isEmpty())
        return;

    _filename = filename.toStdString();

    make_new_algorithm();
    animation_button_active(true);
}

void MainWindow::on_random_button_clicked()
{
    if (ui->num_points_text->text() != "" )
    {
        _number_of_random_points = ui->num_points_text->text().toInt();
    }

    make_new_algorithm();
    animation_button_active(true);
}

void MainWindow::on_clear_button_clicked()
{
    ui->algorithm_type->setCurrentIndex(0);
    animation_button_active(false);
    animation_parameter_button_active(true);

    _canvas->setClear(true);
    _canvas->update();

    _canvas3D->setClear(true);
    _canvas3D->update();

    ui->num_points_text->clear();
    ui->num_points_text->setPlaceholderText("Uneti broj nasumicnih tacaka, podrazumevana vrednost je 20.");
}

void MainWindow::on_start_button_clicked()
{
    ui->start_button->setEnabled(false);
    animation_parameter_button_active(false);
    ui->compare_button->setEnabled(false);

    if (_algorithm)
        _algorithm->startAnimation();
}

void MainWindow::on_pause_resume_button_clicked()
{
    if (_algorithm)
        _algorithm->pauseResumeAnimaiton();
}

void MainWindow::on_next_button_clicked()
{
    if (_algorithm)
        _algorithm->nextAnimation();
}

void MainWindow::on_restart_button_clicked()
{
    ui->start_button->setEnabled(false);
    ui->pause_resume_button->setEnabled(true);
    ui->next_button->setEnabled(true);

    if (_algorithm) {
        _algorithm->stopAnimation();
        make_new_algorithm();
        _algorithm->startAnimation();
    }
}

void MainWindow::on_algorithm_type_currentIndexChanged(int index)
{
    QString current_algorithm = ui->algorithm_type->itemText(index);

    if (current_algorithm == "SA CASOVA VEZBI" || current_algorithm == "STUDENTSKI PROJEKTI") {
        ui->filename_button->setEnabled(false);
        ui->random_button->setEnabled(false);
        animation_button_active(false);
    } else {
        ui->filename_button->setEnabled(true);
        ui->random_button->setEnabled(true);
        animation_button_active(false);
        ui->compare_button->setEnabled(true);
    }
}

void MainWindow::on_compare_button_clicked()
{
    QString algorithm_type = ui->algorithm_type->currentText();

    _thread = new TimeMeasurementThread(algorithm_type, 10, 10, 1200); // TODO: Remove magic constants

    connect(_thread, &TimeMeasurementThread::updateChart, this, &MainWindow::on_line_series_change);
    _thread->start();
}

void MainWindow::on_line_series_change(double dim, double optimal, double naive)
{
    _optimal_series->append(dim, optimal);
    _naive_series->append(dim, naive);
}


void MainWindow::on_animation_end()
{
    ui->algorithm_type->setEnabled(true);
    ui->clear_button->setEnabled(true);
    animation_button_active(false);
    ui->restart_button->setEnabled(true);
}

void MainWindow::make_new_algorithm()
{
    _canvas->setClear(false);
    _canvas3D->setClear(false);

    delete _algorithm;
    _algorithm = nullptr;

    QString algorithm_type = ui->algorithm_type->currentText();

    if (algorithm_type == "MyAlgorithm")
        _algorithm = new MyAlgorithm(_canvas, _canvas3D, _pause_length, _filename, _number_of_random_points);


    if (_algorithm) {
        if (!_algorithm->is3D())
            _canvas->setAlgorithm(_algorithm);
        else
            _canvas3D->setAlgorithm(_algorithm);

        connect(_algorithm, SIGNAL(animationEnded()), this, SLOT(on_animation_end()));
    }
}
