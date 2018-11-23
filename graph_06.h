#ifndef GRAPH_06_H
#define GRAPH_06_H

#include <QtCharts/QtCharts>
#include <QtCharts/QChartView>
#include<QtCharts/QLineSeries>
#include <QtCharts/QSplineSeries>

QT_CHARTS_USE_NAMESPACE

class Graph_06:public QChartView
{
    Q_OBJECT
public:
    Graph_06(QWidget *parent=nullptr);
signals:
    void graph_06_close_signal(QString te);
protected:
    void keyPressEvent(QKeyEvent *event);
    void closeEvent(QCloseEvent *event);
private:
    void switchChartType();
};

#endif // GRAPH_06_H
