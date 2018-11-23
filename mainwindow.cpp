#include "ui_mainwindow.h"
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //connect(portdialog, SIGNAL(Send_Data_To_MainWindow(QString)), this, SLOT());
    connect(Polar_chartView,&Polar::Polar_Close_Singal,this,&MainWindow::Recrive_Data_From_PortDialog);
    connect(Graph_06_chartview,&Graph_06::graph_06_close_signal,this,&MainWindow::Recrive_Data_From_PortDialog);
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
// 画图代码
void MainWindow::on_dis_graph_06_clicked()
{
    if(ui->dis_graph_06->text()==QString::fromLocal8Bit("创建图表"))
    {
        series->clear();
        series->append(0,5);
        series->append(4,10);
        series->append(8,6);
        *series<<QPointF(13,5)<<QPointF(17,6)<<QPointF(20,2);

        chart->legend()->hide();
        chart->addSeries(series);
        chart->createDefaultAxes();//图表会自动将之前的坐标轴清除并新建坐标轴
        chart->setTitle("demo");

        Graph_06_chartview->setChart(chart);
        Graph_06_chartview->setRenderHint(QPainter::Antialiasing);


        Graph_06_chartview->resize(600,600);
        Graph_06_chartview->show();


        //emit close_graph(chart->close());
        ui->dis_graph_06->setText(QString::fromLocal8Bit("关闭图表"));
    }
    else
    {
       Graph_06_chartview->hide();
        chart->removeSeries(series);
        ui->dis_graph_06->setText(QString::fromLocal8Bit("创建图表"));
    }

}

void MainWindow::Recrive_Data_From_PortDialog(QString temp)
{

    if(temp=="graph_06")
    {
        ui->dis_graph_06->setText(QString::fromLocal8Bit("创建图表"));
    }
    else if(temp=="polar_01")
    {
        ui->dis_polar->setText(QString::fromLocal8Bit("创建极坐标"));
    }
}

void MainWindow::on_dis_polar_clicked()
{
    if(ui->dis_polar->text()==QString::fromLocal8Bit("创建极坐标"))
    {
        const qreal angularMin = -100;
        const qreal angularMax = 100;

        const qreal radialMin = -100;
        const qreal radialMax = 100;

        QScatterSeries *series1 = new QScatterSeries();
        series1->setName("scatter");
        for (int i = angularMin; i <= angularMax; i += 10)
            series1->append(i, (i / radialMax) * radialMax + 8.0);

        QSplineSeries *series2 = new QSplineSeries();
        series2->setName("spline");
        for (int i = angularMin; i <= angularMax; i += 10)
            series2->append(i, (i / radialMax) * radialMax);

        QLineSeries *series3 = new QLineSeries();
        series3->setName("star outer");
        qreal ad = (angularMax - angularMin) / 8;
        qreal rd = (radialMax - radialMin) / 3 * 1.3;
        series3->append(angularMin, radialMax);
        series3->append(angularMin + ad*1, radialMin + rd);
        series3->append(angularMin + ad*2, radialMax);
        series3->append(angularMin + ad*3, radialMin + rd);
        series3->append(angularMin + ad*4, radialMax);
        series3->append(angularMin + ad*5, radialMin + rd);
        series3->append(angularMin + ad*6, radialMax);
        series3->append(angularMin + ad*7, radialMin + rd);
        series3->append(angularMin + ad*8, radialMax);

        QLineSeries *series4 = new QLineSeries();
        series4->setName("star inner");
        ad = (angularMax - angularMin) / 8;
        rd = (radialMax - radialMin) / 3;
        series4->append(angularMin, radialMax);
        series4->append(angularMin + ad*1, radialMin + rd);
        series4->append(angularMin + ad*2, radialMax);
        series4->append(angularMin + ad*3, radialMin + rd);
        series4->append(angularMin + ad*4, radialMax);
        series4->append(angularMin + ad*5, radialMin + rd);
        series4->append(angularMin + ad*6, radialMax);
        series4->append(angularMin + ad*7, radialMin + rd);
        series4->append(angularMin + ad*8, radialMax);

        QAreaSeries *series5 = new QAreaSeries();
        series5->setName("star area");
        series5->setUpperSeries(series3);
        series5->setLowerSeries(series4);
        series5->setOpacity(0.5);

        //![1]
        QPolarChart *chart = new QPolarChart();
        //![1]
        chart->addSeries(series1);
        chart->addSeries(series2);
        chart->addSeries(series3);
        chart->addSeries(series4);
        chart->addSeries(series5);

        chart->setTitle("Use arrow keys to scroll, +/- to zoom, and space to switch chart type.");

        //![2]
        QValueAxis *angularAxis = new QValueAxis();
        angularAxis->setTickCount(9); // First and last ticks are co-located on 0/360 angle.
        angularAxis->setLabelFormat("%.1f");
        angularAxis->setShadesVisible(true);
        angularAxis->setShadesBrush(QBrush(QColor(249, 249, 255)));
        chart->addAxis(angularAxis, QPolarChart::PolarOrientationAngular);

        QValueAxis *radialAxis = new QValueAxis();
        radialAxis->setTickCount(9);
        radialAxis->setLabelFormat("%d");
        chart->addAxis(radialAxis, QPolarChart::PolarOrientationRadial);
        //![2]

        series1->attachAxis(radialAxis);
        series1->attachAxis(angularAxis);
        series2->attachAxis(radialAxis);
        series2->attachAxis(angularAxis);
        series3->attachAxis(radialAxis);
        series3->attachAxis(angularAxis);
        series4->attachAxis(radialAxis);
        series4->attachAxis(angularAxis);
        series5->attachAxis(radialAxis);
        series5->attachAxis(angularAxis);

        radialAxis->setRange(radialMin, radialMax);
        angularAxis->setRange(angularMin, angularMax);

        Polar_chartView->setChart(chart);
        Polar_chartView->setRenderHint(QPainter::Antialiasing);

       // ui->dis_polar->setGeometry(50,50,1000,1000);
        Polar_chartView->show();
    //  ui->Polar_dis->setWidget(chartView);
    //  ui->Polar_dis->show();
        ui->dis_polar->setText(QString::fromLocal8Bit("关闭极坐标"));
    }
    else
    {
        Polar_chartView->close();
        ui->dis_polar->setText(QString::fromLocal8Bit("创建极坐标"));
    }



}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton button;
        button = QMessageBox::question(this, QString::fromLocal8Bit("退出程序"),
            QString(QString::fromLocal8Bit("警告：程序有一个任务正在运行中，是否结束操作退出?")),
            QMessageBox::Yes | QMessageBox::No);

        if (button == QMessageBox::No) {
            event->ignore();  //忽略退出信号，程序继续运行
        }
        else if (button == QMessageBox::Yes) {
            event->accept();  //接受退出信号，程序退出
        }

}


