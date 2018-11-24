#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "portdialog.h"
#include "polar.h"
#include "graph_06.h"

#include <QMainWindow>
//#include "serialport_window.h"

#include <QKeyEvent>
#include <QCloseEvent>
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

    void on_dis_graph_06_clicked();

    void Recrive_Signal_From_ChidrenDialog(QString temp);

    void Recrive_Angle_From_ChidrenDialog(float te);

    void Recrive_Num_From_ChidrenDialog(QPointF te);

    void on_dis_polar_clicked();

    void data_dispose();

private:
    Ui::MainWindow *ui;
    PortDialog *portdialog=new PortDialog();

    QChart *chart=new QChart();
    Graph_06 *Graph_06_chartview=new Graph_06();
    Polar *Polar_chartView = new Polar();
    QString yesorno;
    /* 曲线图系列数据 */
    QSplineSeries *series=new QSplineSeries();
    QValueAxis *axisX = new QValueAxis;
    QValueAxis *axisY = new QValueAxis;

    /* 极坐标系列数据  */
    QScatterSeries *series1=new QScatterSeries();
    QSplineSeries *series2 = new QSplineSeries();
    QLineSeries *series3 = new QLineSeries();
    QLineSeries *series4 = new QLineSeries();
    QAreaSeries *series5 = new QAreaSeries();


signals:
    //void close_graph(bool);
protected:
    void closeEvent(QCloseEvent *event);
};

#endif // MAINWINDOW_H
