#ifndef PORTDIALOG_H
#define PORTDIALOG_H

#include <QDialog>
#include <QDebug>
#include <QMessageBox>
#include <QTextStream>
#include <QIODevice>
#include <QFileDevice>
#include <QFileDialog>
#include <QDir>
#include <QString>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QTime>
#include<QtWidgets/QTimeEdit>
#include <QDateTime>
#include "qdatetime.h"
#include <iostream>
#include <qtemporaryfile.h>
#include <Windows.h>
#include <QFloat16>
#include <QKeyEvent>
#include <QPointF>
#include <QString>
using namespace std;

namespace Ui {
class PortDialog;
}

class PortDialog : public QDialog
{
    Q_OBJECT

public:
    //explicit
    PortDialog(QWidget *parent = nullptr);
    ~PortDialog();

private slots:
    void on_open_serial_clicked();

    void Read_Data();

    void on_ClearDataButton_clicked();

    void on_SendDataButton_clicked();

    void on_save_receive_data_clicked();

    bool warrning();

    bool data_Check(QByteArray data,QByteArray erc);

    void Search_Serial_Port();


    void keyPressEvent(QKeyEvent *event);

signals:
    void Send_Data_To_MainWindow(QString te);
    void Send_Angle_Data_To_MainWindow(QString signal, float te);
    void Send_Num_Data_To_MainWindow(QPointF te);


protected:
    void Dispose_buf_data();


private:
    Ui::PortDialog *ui;

    //需要清零
    QByteArray buf,Check,erc,data;
    int step=0;
    char te='\x00';
    int times=0;

    //不需要清零
    QSerialPort *serial;
    QString Save_filename;
    QString Open_filename;
    QString str_time;
    QDateTime time1=QDateTime::currentDateTime();
    QDir *dir=new QDir();
    QFile *file=new QFile();
    QString data_number;





};

#endif // PORTDIALOG_H
