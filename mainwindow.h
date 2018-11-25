#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "portdialog.h"
#include "polar.h"
#include "graph_06.h"

#include <QMainWindow>
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

    void Recrive_Angle_From_ChidrenDialog(QString signal, float te);

    void Recrive_Num_From_ChidrenDialog(QPointF te);

    void on_dis_polar_clicked();

    void data_dispose();

private:
    Ui::MainWindow *ui;

    /* 串口系列变量 */
    PortDialog *portdialog=new PortDialog();
    QString yesorno;

    QChart *chart=new QChart();

    /* 曲线图系列数据 */
    Graph_06 *Graph_06_chartview=new Graph_06();
    QSplineSeries *series=new QSplineSeries();
    QValueAxis *axisX = new QValueAxis;
    QValueAxis *axisY = new QValueAxis;

    /* 极坐标系列数据  */
    Polar *Polar_chartView = new Polar();
    QSplineSeries *angle_series=new QSplineSeries();
    QScatterSeries *series1=new QScatterSeries();
    QSplineSeries *series2 = new QSplineSeries();
    QLineSeries *series3 = new QLineSeries();
    QLineSeries *series4 = new QLineSeries();
    QAreaSeries *series5 = new QAreaSeries();


    /* 接收数据 */
    float angle=0;
signals:
    //void close_graph(bool);
protected:
    void closeEvent(QCloseEvent *event);
};

#endif // MAINWINDOW_H
