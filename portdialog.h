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

namespace Ui {
class PortDialog;
}

class PortDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PortDialog(QWidget *parent = nullptr);
    ~PortDialog();

private slots:
    void on_open_serial_clicked();

    void Read_Data();

    void on_ClearDataButton_clicked();

    void on_SendDataButton_clicked();

    void on_save_receive_data_clicked();

    bool warrning();

    void dispose_16_data(QVector<QString> &data,QString tempdata);

private:
    Ui::PortDialog *ui;
    QSerialPort *serial;
    QString Save_filename;
    QString Open_filename;
    QString str_time;
    QDateTime time1=QDateTime::currentDateTime();
    QDir *dir=new QDir();
    QFile *file=new QFile();
};

#endif // PORTDIALOG_H
