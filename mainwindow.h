#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
//#include "serialport_window.h"
#include "portdialog.h"
#include <QtCharts/QtCharts>
#include <QtCharts/QChartView>
#include<QtCharts/QLineSeries>
#include <QtCharts/QSplineSeries>
#include <QKeyEvent>

using namespace QtCharts;


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_action_triggered();

    void on_create_graph_clicked();

    void Recrive_Data_From_PortDialog(QString receive_data);



private:
    Ui::MainWindow *ui;
    PortDialog *portdialog;

    QChart *chart=new QChart();
    QChartView *chartview=new QChartView(chart);

    QSplineSeries *series=new QSplineSeries();

};

#endif // MAINWINDOW_H
