#include "portdialog.h"
#include "ui_portdialog.h"

PortDialog::PortDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PortDialog)
{
    ui->setupUi(this);
    //查找可用串口

    foreach (const  QSerialPortInfo &info,QSerialPortInfo::availablePorts())
        {
            QSerialPort serial;
            serial.setPort(info);
            auto a=info.description();
            qDebug()<<a;
            if (a==QString::fromLocal8Bit("蓝牙链接上的标准串行"))
            {
                continue;
            }
            else
            {
                ui->PortBox->addItem(serial.portName());
                serial.close();
            }
        }
    //设置波特率下拉菜单默认显示第三项
    //ui->BaudBox->setCurrentIndex(3);
    //关闭发送按钮使能
    ui->SendDataButton->setEnabled(false);
    qDebug()<<QString::fromLocal8Bit("界面设定成功");
     qDebug()<<QString::fromLocal8Bit("搜寻串口成功");
}

PortDialog::~PortDialog()
{
    delete ui;
}


void PortDialog::on_open_serial_clicked()
{
    //建立存储文件
    Save_filename=Open_filename +time1.toString("hh.mm.ss")+".txt";
    //判断文件
    if(ui->open_serial->text()==QString::fromLocal8Bit("打开串口")&&warrning())
    {        
        serial= new QSerialPort;
        //设置串口名
        serial->setPortName(ui->PortBox->currentText());
        qDebug()<<QString::fromLocal8Bit("设置串口名成功");
        //打开串口
        serial->open(QIODevice::ReadWrite);
        qDebug()<<QString::fromLocal8Bit("打开串口成功");
        //设置波特率
        serial->setBaudRate(ui->BaudBox->currentText().toInt());
        //设置数据位
		
		switch (ui->BitBox->currentIndex())
		{
        case 8:

            serial->setDataBits(QSerialPort::Data8);
			qDebug() << QString::fromLocal8Bit("设置数据位成功");
			break;
		}
        //设置奇偶校验位
        switch (ui->ParityBox->currentIndex())
        {
        case 0:
            serial->setParity(QSerialPort::NoParity);
            qDebug()<<QString::fromLocal8Bit("设置奇偶校验位成功");
            break;
        default:break;
        }
        //设置停止位
        switch (ui->StopBox->currentIndex())
        {
        case 0:
            serial->setStopBits(QSerialPort::OneStop);
            qDebug()<<QString::fromLocal8Bit("设置停止位0成功");
            break;
        case 1:
              serial->setStopBits(QSerialPort::TwoStop);
              qDebug()<<QString::fromLocal8Bit("设置停止位1成功");
            break;
        default:break;
        }

        //设置控制流
        serial->setFlowControl(QSerialPort::NoFlowControl);
        //关闭设置菜单使能
        ui->PortBox->setEnabled(false);
        ui->PortBox->setEnabled(false);
        ui->BaudBox->setEnabled(false);
        ui->BitBox->setEnabled(false);
        ui->ParityBox->setEnabled(false);
        ui->StopBox->setEnabled(false);
        ui->open_serial->setText(QString::fromLocal8Bit("关闭串口"));
        ui->SendDataButton->setEnabled(true);
        qDebug()<<QString::fromLocal8Bit("打开串口成功");
        //连接信号槽
        QObject::connect(serial,&QSerialPort::readyRead,this,&PortDialog::Read_Data);

    }
    else if(ui->open_serial->text()==QString::fromLocal8Bit("关闭串口"))
    {
       // times++;
        //关闭串口
        serial->clear();
        serial->close();
        serial->deleteLater();
        //恢复设置使能
       // ui->PortBox->setEnabled(true);
        ui->PortBox->setEnabled(true);
        ui->BaudBox->setEnabled(true);
        ui->BitBox->setEnabled(true);
        ui->ParityBox->setEnabled(true);
        ui->StopBox->setEnabled(true);
        ui->open_serial->setText(QString::fromLocal8Bit("打开串口"));
        ui->SendDataButton->setEnabled(false);
        file->close();
    }

}

void PortDialog::Read_Data()
{


//    QDir tempdir(Open_filename);
//    tempdir.mkdir("test");
//    qDebug()<<tempdir.absoluteFilePath("test");

    //qDebug()<<Save_filename;

   QFile file(Save_filename);
    if(!file.open(QIODevice::WriteOnly|QIODevice::Append))
    {
       file.close();
    }
    str_time=time1.toString("yyyy-MM-dd hh:mm:ss");
    QByteArray buf;
    buf = serial->readAll();
    ui->Receive_Window->document()->setMaximumBlockCount(100);
    if(!buf.isEmpty())
    {
        QTextStream out(&file);
        qDebug()<<QString::fromLocal8Bit("接收数据成功");
        out<<str_time<<" "<<QString::fromLocal8Bit(buf)<<"\n";
        QString str=ui->Receive_Window->toPlainText();
        str+=QString::fromLocal8Bit(buf);
        ui->Receive_Window->clear();
        ui->Receive_Window->append(str);
        //file.close();
    }
    else
    {
        QTextStream out(&file);
        out<<str_time<<" "<<QString::fromLocal8Bit("串口无数据");
    }
    time1=QDateTime::currentDateTime();
   buf.clear();
}

void PortDialog::on_ClearDataButton_clicked()
{
    ui->Receive_Window->clear();
}

void PortDialog::on_SendDataButton_clicked()
{
    serial->write(ui->Send_Window->toPlainText().toLatin1());
}

void PortDialog::on_save_receive_data_clicked()
{
    Open_filename=QFileDialog::getExistingDirectory(this,QString::fromLocal8Bit("保存串口数据"),"/home",QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks);
    Open_filename+="/";
}

bool PortDialog::warrning()
{
    if(Open_filename==QString())
    {
        QMessageBox::information(nullptr,"critical",QString::fromLocal8Bit("没有选择存储路径"),QMessageBox::Yes);
        return false;
    }
    return true;
}
