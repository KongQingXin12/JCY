﻿#include "ui_mainwindow.h"
#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //connect(Polar_chartView,SIGNAL(Polar_Close_Singal),this,SLOT(Recrive_Signal_From_ChidrenDialog));

    /* 极坐标信号与槽 */
    connect(Polar_chartView,&Polar::Polar_Close_Singal,this,&MainWindow::Recrive_Signal_From_ChidrenDialog);
    /* 曲线坐标信号与槽 */
    connect(Graph_06_chartview,&Graph_06::graph_06_close_signal,this,&MainWindow::Recrive_Signal_From_ChidrenDialog);
    /* 串口信号与槽 */
    connect(portdialog,&PortDialog::Send_Data_To_MainWindow,this,&MainWindow::Recrive_Signal_From_ChidrenDialog);
    connect(portdialog,&PortDialog::Send_Num_Data_To_MainWindow,this,&MainWindow::Recrive_Num_From_ChidrenDialog);
    connect(portdialog,&PortDialog::Send_Angle_Data_To_MainWindow,this,&MainWindow::Recrive_Angle_From_ChidrenDialog);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_action_triggered()
{
    portdialog->show();

}
// 画图代码
void MainWindow::on_dis_graph_06_clicked()
{
    if(ui->dis_graph_06->text()==QString::fromLocal8Bit("创建图表"))
    {

        axisX->setRange(0,1000);
        axisX->setLabelFormat("%g");
        axisX->setTitleText("axisX");

        axisY->setRange(0,122880);
        axisY->setTitleText("axisY");

        chart->setAxisX(axisX,series);
        chart->setAxisY(axisY,series);

        chart->legend()->hide();
        chart->setTitle("demo");

        chart->addSeries(series);
        chart->setAnimationOptions(QChart::SeriesAnimations);
        //chart->createDefaultAxes();//图表会自动将之前的坐标轴清除并新建坐标轴

        Graph_06_chartview->setChart(chart);
        Graph_06_chartview->setRenderHint(QPainter::Antialiasing);


        Graph_06_chartview->resize(600,600);
        Graph_06_chartview->show();


        //emit close_graph(chart->close());
        ui->dis_graph_06->setText(QString::fromLocal8Bit("关闭图表"));
    }
    else
    {

       Graph_06_chartview->close();
        chart->removeSeries(series);
       // chart->close();
        ui->dis_graph_06->setText(QString::fromLocal8Bit("创建图表"));
    }

}

void MainWindow::Recrive_Signal_From_ChidrenDialog(QString temp)
{
qDebug()<<temp;
    if(temp=="graph_06")
    {
        ui->dis_graph_06->setText(QString::fromLocal8Bit("创建图表"));
        series->clear();
        chart->removeSeries(series);
    }
    else if(temp=="polar_01")
    {
        ui->dis_polar->setText(QString::fromLocal8Bit("创建极坐标"));
    }
    else if(temp=="port_stop")
    {
        Graph_06_chartview->close();
        ui->dis_graph_06->setText(QString::fromLocal8Bit("创建图表"));
        series->clear();
    }
}

void MainWindow::Recrive_Angle_From_ChidrenDialog(QString signal, float te)
{
    if(signal=="start")
    {
        if(!qFuzzyCompare(angle,te))
        {
            angle=te;
        }
    }

}

void MainWindow::Recrive_Num_From_ChidrenDialog(QPointF te)
{
    series->append(te);
    //qDebug()<<te.x()<<" "<<te.y();
    if(te.x()>=1000)
    {
        axisX->setRange(te.x()-1000,te.x());
    }

    static QTime dataTime(QTime::currentTime());
    long int eltime = dataTime.elapsed();
    static int lastpointtime = 0;
    int size = (eltime - lastpointtime);//数据个数
    //qDebug()<<"size-->"<<size;
    {
                QVector<QPointF> oldPoints = series->pointsVector();//Returns the points in the series as a vector
                QVector<QPointF> points;

                for(int i=size;i<oldPoints.count();++i){
                    points.append(QPointF(i-size ,oldPoints.at(i).y()));//替换数据用
                }
                qint64 sizePoints = points.count();
                for(int k=0;k<size;++k){
                    points.append(QPointF(k+sizePoints,te.y()));
                }
                series->replace(points);
                lastpointtime = eltime;
           }


}

void MainWindow::on_dis_polar_clicked()
{
    if(ui->dis_polar->text()==QString::fromLocal8Bit("创建极坐标"))
    {
        const qreal angularMin = -180;
        const qreal angularMax = 180;

        const qreal radialMin = 0;
        const qreal radialMax = 100;

//        series1->setName("scatter");
//        for (int i = angularMin; i <= angularMax; i += 10)
//            series1->append(i, (i / radialMax) * radialMax + 8.0);

//        series2->setName("spline");
//        for (int i = angularMin; i <= angularMax; i += 10)
//            series2->append(i, (i / radialMax) * radialMax);

        series3->setName("star outer");

        qreal ad = (angularMax - angularMin) / 8;
        qreal rd = (radialMax - radialMin) / 3 * 1.3;
		vector<pair<int, int>>te_series3;
        series3->append(angularMin, radialMax+10);
       // series3->append(angularMin,radialMin);
//		te_series3.push_back(make_pair(angularMin, radialMax));
       series3->append(angularMin + ad, radialMax+10);

//		te_series3.push_back(make_pair(angularMin + ad * 1, radialMin + rd));
//        series3->append(angularMin + ad*2, radialMax);
//		te_series3.push_back(make_pair(angularMin + ad * 2, radialMax));
//        series3->append(angularMin + ad*3, radialMin + rd);
//		te_series3.push_back(make_pair(angularMin + ad * 3, radialMin + rd));
//        series3->append(angularMin + ad*4, radialMax);
//		te_series3.push_back(make_pair(angularMin + ad * 4, radialMax));
//        series3->append(angularMin + ad*5, radialMin + rd);
//		te_series3.push_back(make_pair(angularMin + ad * 5, radialMin + rd));
//        series3->append(angularMin + ad*6, radialMax);
//		te_series3.push_back(make_pair(angularMin + ad * 6, radialMax));
//        series3->append(angularMin + ad*7, radialMin + rd);
//		te_series3.push_back(make_pair(angularMin + ad * 7, radialMin + rd));
//        series3->append(angularMin + ad*8, radialMax);
//		te_series3.push_back(make_pair(angularMin + ad * 8, radialMax));

        series4->setName("star inner");
        ad = (angularMax - angularMin) / 8;
        rd = (radialMax - radialMin) / 3;
        series4->append(angularMin, radialMax-99);
  //      series4->append(angularMin+4,radialMin);
        series4->append(angularMin + ad*1, radialMax-99);
//        series4->append(angularMin + ad*2, radialMax);
//        series4->append(angularMin + ad*3, radialMin + rd);
//        series4->append(angularMin + ad*4, radialMax);
//        series4->append(angularMin + ad*5, radialMin + rd);
//        series4->append(angularMin + ad*6, radialMax);
//        series4->append(angularMin + ad*7, radialMin + rd);
//        series4->append(angularMin + ad*8, radialMax);

        series5->setName("star area");
        series5->setUpperSeries(series3);
        series5->setLowerSeries(series4);
        series5->setOpacity(0.5);

        //![1]
        QPolarChart *chart = new QPolarChart();
        //![1]
//        chart->addSeries(series1);
//        chart->addSeries(series2);
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

//        series1->attachAxis(radialAxis);
//        series1->attachAxis(angularAxis);
//        series2->attachAxis(radialAxis);
//        series2->attachAxis(angularAxis);
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

void MainWindow::data_dispose()
{

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

void MainWindow::paintEvent(QPaintEvent *event)
{


    /* 绘制第一个圆环 */
	QPainter painter1(this);
	painter1.begin(this);
	painter1.setRenderHint(QPainter::Antialiasing);//设置圆滑绘制风格（抗锯齿）
   //绘制圆环
	float m_persent1 = angle;//此处我画80%
    int m_rotateAngle1 = 180* (1 - m_persent1 / 100);
	int side1 = qMin(width(), height());
	//定义矩形绘制区域
	QRectF outRect1(50, 80, 200, 200);
	QRectF inRect1(70, 100, 200 - 40, 200 - 40);
	//转换需要绘出的值
	QString valueStr1 = QString("%1%").arg(QString::number(m_persent1));

	//画外圆
	painter1.setPen(Qt::NoPen);
	painter1.setBrush(QBrush(QColor(255, 107, 107)));//红色
    painter1.drawPie(outRect1, 0 * 16, 180 * 16);
	//画内圆
	painter1.setBrush(QBrush(QColor(97, 117, 118)));//黑色
    painter1.drawPie(outRect1, 0 * 16, m_rotateAngle1 * 16);
	//画遮罩，遮罩颜色为窗口颜色
	painter1.setBrush(palette().window().color());
	painter1.drawEllipse(inRect1);
	//画文字
	QFont f1 = QFont("Microsoft YaHei", 15, QFont::Bold);
	painter1.setFont(f1);
	painter1.setFont(f1);
	painter1.setPen(QColor("#555555"));
	painter1.drawText(inRect1, Qt::AlignCenter, valueStr1);
	painter1.end();

	/* 绘制第二个圆环 */
	QPainter painter2(this);
	painter2.begin(this);
	painter2.setRenderHint(QPainter::Antialiasing);//设置圆滑绘制风格（抗锯齿）
//绘制圆环
	float m_persent2 = angle;//此处我画80%
    int m_rotateAngle2 = 180 * (1 - m_persent2 / 100);
	int side2 = qMin(width(), height());
	//定义矩形绘制区域
	QRectF outRect2(50, 280, 200, 200);
	QRectF inRect2(70, 300, 200 - 40, 200 - 40);
	//转换需要绘出的值
	QString valueStr2 = QString("%1%").arg(QString::number(m_persent2));

	//画外圆
	painter2.setPen(Qt::NoPen);
	painter2.setBrush(QBrush(QColor(255, 107, 107)));//红色
    painter2.drawPie(outRect2, 0 * 16, 180 * 16);
	//画内圆
	painter2.setBrush(QBrush(QColor(97, 117, 118)));//黑色
    painter2.drawPie(outRect2, 0 * 16, m_rotateAngle2 * 16);
	//画遮罩，遮罩颜色为窗口颜色
	painter2.setBrush(palette().window().color());
	painter2.drawEllipse(inRect2);
	//画文字
	QFont f2 = QFont("Microsoft YaHei", 15, QFont::Bold);
	painter2.setFont(f2);
	painter2.setFont(f2);
	painter2.setPen(QColor("#555555"));
	painter2.drawText(inRect2, Qt::AlignCenter, valueStr2);
	painter2.end();
}




void MainWindow::on_pushButton_clicked()
{
#ifdef Q_OS_WIN
    QString extraImportPath(QStringLiteral("%1/../../../../%2"));
#else
    QString extraImportPath(QStringLiteral("%1/../../../%2"));
#endif
    viewer.engine()->addImportPath(extraImportPath.arg(QGuiApplication::applicationDirPath(),         QString::fromLatin1("qml")));
    QObject::connect(viewer.engine(), &QQmlEngine::quit, &viewer, &QWindow::close);
    MainWindow mw;
    viewer.engine()->rootContext()->setContextProperty("mw", &mw);
    viewer.setTitle(QStringLiteral("QML Chart"));
    viewer.setSource(QUrl::fromLocalFile("JCY/qml_temp/view1.qml"));
    viewer.setResizeMode(QQuickView::SizeRootObjectToView);
    viewer.show();

}


