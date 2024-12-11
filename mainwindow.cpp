#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    // Получаем значения шага и пределов из QLineEdit
    double stepX = ui->xStepLineEdit->text().toDouble();
    double xMin = ui->xLeftlineEdit->text().toDouble();
    double xMax = ui->xRightlineEdit->text().toDouble();

    // Убедимся, что шаг положительный
    if (stepX <= 0) {
        stepX = 0.01; // Значение по умолчанию
    }

    // Создаем серию для x >= 3
    QLineSeries *series1 = new QLineSeries();
    for (double x = std::max(3.0, xMin); x <= xMax; x += stepX) {
        double y = x * x - 8 * x + 13;
        series1->append(x, y);
    }
    series1->setName("y = x² - 8x + 13");

    // Создаем серию для x < 3
    QLineSeries *series2 = new QLineSeries();
    for (double x = xMin; x < 3 && x <= xMax; x += stepX) {
        double y = x - 5;
        series2->append(x, y);
    }
    series2->setName("y = x - 5");

    // Создаем объект QChart и добавляем серии
    QChart *chart = new QChart();
    chart->addSeries(series1);
    chart->addSeries(series2);
    chart->createDefaultAxes();
    chart->setTitle("Кусочная функция");
    chart->legend()->setAlignment(Qt::AlignBottom);

    // Создаём QChartView для отображения QChart
    QChartView* chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing); // Улучшение качества отрисовки

    chartView->setFixedSize(ui->graphicsView->viewport()->size());

    QGraphicsScene* scene = new QGraphicsScene(this);
    scene->addWidget(chartView);
    scene->setSceneRect(0, 0, ui->graphicsView->width(), ui->graphicsView->height());

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

