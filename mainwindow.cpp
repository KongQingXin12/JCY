#include "ui_mainwindow.h"
#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->Graph_dis->close();
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_action_triggered()
{
    portdialog=new PortDialog(this);
    portdialog->show();
}

void MainWindow::on_create_graph_clicked()
{
    if(ui->create_graph->text()==QString::fromLocal8Bit("创建图表"))
    {
        series->append(0,5);
        series->append(4,10);
        series->append(8,6);
        *series<<QPointF(13,5)<<QPointF(17,6)<<QPointF(20,2);


        chart->legend()->hide();
        chart->addSeries(series);
        chart->createDefaultAxes();
        chart->setTitle("demo");


        chartview->setRenderHint(QPainter::Antialiasing);
        chartview->setWindowTitle("demo");

        chartview->resize(400,300);
        //chartview->show();


        ui->Graph_dis->setWidget(chartview);
        ui->Graph_dis->show();
        ui->create_graph->setText(QString::fromLocal8Bit("关闭图表"));
    }
    else
    {
        ui->Graph_dis->hide();
        series->clear();
        ui->create_graph->setText(QString::fromLocal8Bit("创建图表"));
    }

}


