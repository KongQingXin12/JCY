#include "portdialog.h"
#include "ui_portdialog.h"

PortDialog::PortDialog(QWidget *parent) :
    QDialog(parent,Qt::WindowTitleHint|Qt::CustomizeWindowHint),
    ui(new Ui::PortDialog)
{
    ui->setupUi(this);
    //查找可用串口
    Search_Serial_Port();
    //设置波特率下拉菜单默认显示第三项
    //ui->BaudBox->setCurrentIndex(3);
    ui->dis_num_sdj->setPalette(Qt::white);
    ui->dis_ang_sdj->setPalette(Qt::white);
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
        case 0:
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
    buf += serial->readAll();
    //qDebug() << buf;
    //qDebug() << buf.at(0);
	//创建数据存储文件
    str_time=time1.toString("yyyy-MM-dd hh:mm:ss");
	//接收数据
	//QByteArray buf;
    //buf = serial->readAll();
    //qDebug()<<buf;
    //qDebug()<<buf.size();
    Dispose_buf_data();
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
    QString temppath=dir->currentPath();
	qDebug() << temppath;
    Open_filename=QFileDialog::getExistingDirectory(this,QString::fromLocal8Bit("保存串口数据"),temppath,QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks);
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

bool PortDialog::data_Check(QByteArray data, QByteArray erc)
{
    QString d=data.toHex();
    QString e=erc.toHex();
    auto i=d.rbegin();
    auto j=e.rbegin();
    for(;j!=e.rend();i++,j++)
    {
        if(*i!=*j)
        {
            return false;
        }
    }
    return true;
}

void PortDialog::Search_Serial_Port()
{
	foreach(const  QSerialPortInfo &info, QSerialPortInfo::availablePorts())
	{
		QSerialPort serial;
		serial.setPort(info);
		auto a = info.description();
		qDebug() << a;
		if (a == QString::fromLocal8Bit("蓝牙链接上的标准串行"))
		{
			continue;
		}
		else
		{
			ui->PortBox->addItem(serial.portName());
			serial.close();
		}
	}
}


void PortDialog::Dispose_buf_data()
{
    QFile file(Save_filename);

    if(!file.open(QIODevice::WriteOnly|QIODevice::Append))
    {
       file.close();
    }
    if(buf.size()>=16)
    {
        for(int i=0;i<buf.size();i++)
        {
            if(buf[i]=='\x55')
            {
                step=1;
            }
            else if(buf[i]=='\xaa')
            {
                step=2;
            }
            else if(step==2)
            {
                switch (buf[i])
                {
                case '\x06':
                    step=3;
                    break;
                }
            }
            else if(step==3)
            {
                while (data.size()<4)
                {
                    data += buf[i];
                    te+=buf[i];
                    i++;
                }
                if(data.size()==4)
                {
                    te += '\x06';
                    te=te&'\xff';
                    Check+=te;
                    step=4;
                    te='\x00';
                    i--;
                }
            }
            else if(step==4)
            {
                erc+=buf[i];
                step++;
                if (step == 5)
                {
                    if (data_Check(Check, erc))
                    {
                        string ss = data.toHex().toStdString();
                        long long a = 0;
                        for (auto i = ss.rbegin(); i !=ss.rend(); i++)
                        {
                            int n = distance(ss.rbegin(), i);
                            if (*i >= 'a'&&*i <= 'f')
                            {
                                a += pow(16, n)*(*i - 'a' + 10);
                            }
                            else
                            {
                                a += pow(16, n)*(*i - '0');
                            }
                        }
                        data.clear();
                        ss=to_string(a);
                        data_number=QString::fromStdString(ss);
                        //显示处理结果
                        ui->Receive_Window->clear();
                        ui->Receive_Window->append(QString::fromStdString(to_string(a)));
                        ui->Receive_Window->append(QString::fromLocal8Bit("校验成功，数据合格"));
                        //LCD显示处理结果-整数
                        ui->dis_num_sdj->display(data_number);
                        emit Send_Data_To_MainWindow(data_number);
                        //LCD显示处理结果-角度
                        float angl;
                        if(a<=61440)
                        {
                            angl=(float)a*12/4096;
                        }
                        else
                        {
                            angl=(float)a-122880*12/4096;
                        }

                        ui->dis_ang_sdj->display(QString("%1").arg(angl));
                        QTextStream in(&file);
                        in << str_time + " " + "55aa" +" "<< a << " " + erc.toHex() << "\r\n";
                        file.close();
                    }
                    else
                    {
                        if(data.size()==4)
                            data.clear();
                        ui->Receive_Window->clear();
                        ui->Receive_Window->append(QString::fromLocal8Bit("校验失败"));
                    }
                    if (buf.size() == 8)
                        buf.clear();
                    else
                        buf = buf.mid(i);
                    step = 0;
                    Check.clear();
                    erc.clear();
                    break;
                }

            }
        }
    }

}

void PortDialog::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Escape:
        hide();
        qDebug()<<QString::fromLocal8Bit("隐藏窗口不关闭");
        break;
    default:
        QDialog::keyPressEvent(event);
    }
}








