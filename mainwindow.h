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

    void Recrive_Data_From_PortDialog(QString te);

    void on_dis_polar_clicked();

private:
    Ui::MainWindow *ui;
    PortDialog *portdialog;

    QChart *chart=new QChart();
    Graph_06 *Graph_06_chartview=new Graph_06();
    Polar *Polar_chartView = new Polar();
    QSplineSeries *series=new QSplineSeries();
    QString yesorno;
signals:
    //void close_graph(bool);
protected:
    void closeEvent(QCloseEvent *event);
};

#endif // MAINWINDOW_H
