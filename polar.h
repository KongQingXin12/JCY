#ifndef POLAR_H
#define POLAR_H

#include <QtCharts/QChartView>
#include <QtCharts/QPolarChart>
#include <QMessageBox>
QT_CHARTS_USE_NAMESPACE

class Polar : public QChartView
{
    Q_OBJECT
public:
    Polar(QWidget *parent = nullptr);
signals:
    void Polar_Close_Singal(QString te,int te1);

protected:
    void keyPressEvent(QKeyEvent *event);
    void closeEvent(QCloseEvent *event);

private:
    void switchChartType();

};

#endif // POLAR_H
