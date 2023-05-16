#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    myfilesave=new filesave();
    QThread *mptfileThread=new QThread();
    myfilesave->moveToThread(mptfileThread);
    mptfileThread->start();

    mpDataCard =new myDateCard ();
    QThread *mptDataThread=new QThread();
    mpDataCard->moveToThread(mptDataThread);
    mptDataThread->start();
    mpChart =new mychart(ui);
    mpChart->Chart_Cinit();
    mpChart->Chart_Origininit();



    connect(this,SIGNAL(connectD()),mpDataCard,SLOT (connectDevice()));
    connect(this,SIGNAL(startSamTimer(bool)),mpDataCard,SLOT (timerTriger(bool)));

    connect(this,SIGNAL(sendConfig(QList<QString>)),mpDataCard,SLOT (receiveConfig(QList<QString>)));

    connect(mpDataCard,SIGNAL(sendDate2Chart(QVector <double>,QVector <double>)),mpChart,SLOT (receiveDate2Chart(QVector <double>,QVector <double>)));

    connect(mpDataCard,SIGNAL(sendCOCN2Chart(QVector <double>)),mpChart,SLOT (receiveCOCN2Chart(QVector <double>)));

     connect(mpDataCard,SIGNAL(connectsuccess(bool)),this,SLOT (openlock(bool)));



    connect(mpDataCard,SIGNAL(saveCOCN(QVector <double>,QString)),myfilesave,SLOT (savecocnData(QVector <double>,QString)));
    connect(mpDataCard,SIGNAL(saveoprigin(QVector <double>,QVector <double>,QString)),myfilesave,SLOT (saveORIGNData(QVector <double>,QVector <double>,QString)));
    connect(mpDataCard,SIGNAL( sendbar2main(float)),this,SLOT (receiveBar(float)));

   connect(mpDataCard,SIGNAL( sendCOCN2main(QVector<double>)),this,SLOT (receiveCOCN2main(QVector<double>)));

    connect(ui->myOriginChart, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(myMoveEvent(QMouseEvent*)));

}

void MainWindow::myMoveEvent(QMouseEvent *event) {
    //获取鼠标坐标，相对父窗体坐标
    int x_pos = event->pos().x();
    int y_pos = event->pos().y();

    //鼠标坐标转化为CustomPlot内部坐标
    float x_val = ui->myOriginChart->xAxis->pixelToCoord(x_pos);
    float y_val = ui->myOriginChart->yAxis->pixelToCoord(y_pos);

    QString str,strToolTip;
    str = QString::number(x_val, 10, 3);
    strToolTip += "x: ";
    strToolTip += str;
    strToolTip += "\n";

    for (int i = 0;i <2;i++)
    {
        //获得x轴坐标位置对应的曲线上y的值
        float y = ui->myOriginChart->graph(i)->data()->at(x_val)->value;
        str = QString::number(y);
        strToolTip += "通道" + QString::number(i+1) + "：";
        strToolTip += str;
        strToolTip += "\n";
    }
    QToolTip::showText(cursor().pos(), strToolTip, ui->myOriginChart);
}

 void MainWindow::openlock(bool mFLG)
 {
     if(mFLG)
     {
         ui->startSample->setEnabled(true);
         ui->connectDev->setText("断开连接");
     }
     else
     {
         ui->startSample->setEnabled(false);
         ui->connectDev->setText("连接设备");
     }

 };
 void MainWindow:: receiveBar(float mbar)
 {
     ui->qiya->setText(QString::number(mbar)+"kpa");
 };

 void MainWindow::receiveCOCN2main(QVector<double> myba)
 {
     ui->nongdu_1->setText(QString::number(myba[1])+"ppm");
     ui->nongdu_2->setText(QString::number(myba[2])+"ppm");
 };

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::checkSampleFlag()
{
    return isSampling;
}
void MainWindow::on_connectDev_clicked()
{
    emit connectD();
  //  ui->startSample->setEnabled(true);
}


void MainWindow::on_startSample_clicked()
{
    if(checkSampleFlag())
    {
       emit startSamTimer(false);
       isSampling=false;
       ui->startSample->setText("开始采集");

       ui->frame_3->setEnabled(true);
       ui->groupBox->setEnabled(true);
       ui->groupBox_2->setEnabled(true);
       ui->writeconfig->setEnabled(true);

    }
    else
    {
       emit startSamTimer(true);
        isSampling=true;
        ui->startSample->setText("停止采集");


        ui->frame_3->setEnabled(false);
        ui->groupBox->setEnabled(false);
        ui->groupBox_2->setEnabled(false);
        ui->writeconfig->setEnabled(false);

    }

}

void MainWindow::on_pushButton_fileselect_clicked()
{
    QString srcDirPath = QFileDialog::getExistingDirectory(

    this, "choose src Directory",

    "/");

    if (srcDirPath.isEmpty())

    {

    return;

    }

    else

    {

     ui->COCN_filepath->setText( srcDirPath += "/");

   ;

    }

}

//void MainWindow::on_setConfig_clicked()
//{
//    bool ok;
//     QString text = QInputDialog::getText(this, tr("后台管理"),tr("请输入配置密码"), QLineEdit::Password,0, &ok);
//     if (ok && !text.isEmpty())
//     {
//         if(text=="1023")
//         {
//            if(setLocked)
//            {
//                ui->frame->setEnabled(true);
//                setLocked=false;
//                ui->setConfig->setText("关闭配置参数锁");
//            }
//            else
//            {
//                ui->frame->setEnabled(false);
//                ui->setConfig->setText("开启配置参数锁");
//                setLocked=true;
//            }


//         }
//         else
//         {
//            QMessageBox ms;
//            ms.setIcon(QMessageBox::Icon::Warning);
//            ms.setWindowIcon(QIcon(":/image/image/001.jpg"));
//            ms.setWindowTitle("注意");
//            ms.setText("密码错误！");
//            ms.exec();

//         }
//     }
//     else
//     {
//         QMessageBox ms;
//         ms.setIcon(QMessageBox::Icon::Warning);
//         ms.setWindowIcon(QIcon(":/image/image/001.jpg"));
//         ms.setWindowTitle("注意");
//         ms.setText("密码不能为空！");
//         ms.exec();
//     }
//}





void MainWindow::on_writeconfig_clicked()
{
    QList<QString> mylist;

    mylist.append(ui->COCN_filepath->text()); //0
    mylist.append(ui->countTime->text());//1
    mylist.append(ui->MAX1_B1->text());//2
    mylist.append(ui->MAX1_B2->text());//3
    mylist.append(ui->MIN1_B1->text());//4
    mylist.append(ui->MIN1_B2->text());//5

    mylist.append(ui->MAX2_B1->text());//6
    mylist.append(ui->MAX2_B2->text());//7
    mylist.append(ui->MIN2_B1->text());//8
    mylist.append(ui->MIN2_B2->text());//9

    if(ui->ifCount->isChecked())
    {
        mylist.append("1");
    }
    else
    {
        mylist.append("0");
    }
    if(ui->ifMAX_MIN->isChecked())
    {
        mylist.append("1");
    }
    else
    {
        mylist.append("0");
    }
//==================================================
    if(ui->F_1_MAX1_selected->isChecked())
    {
         mylist.append("1");
    }
    else
    {
         mylist.append("0");
    }
    if(ui->F_1_MAX2_selected->isChecked())
    {
         mylist.append("1");
    }
    else
    {
         mylist.append("0");
    }
    if(ui->F_1_MIN1_selected->isChecked())
    {
         mylist.append("1");
    }
    else
    {
         mylist.append("0");
    }
    if(ui->F_1_MIN2_selected->isChecked())
    {
         mylist.append("1");
    }
    else
    {
         mylist.append("0");
    }
    if(ui->F_2_MAX1_selected->isChecked())
    {
         mylist.append("1");
    }
    else
    {
         mylist.append("0");
    }

    if(ui->F_2_MAX2_selected->isChecked())
    {
         mylist.append("1");
    }
    else
    {
         mylist.append("0");
    }


    if(ui->F_2_MIN1_selected->isChecked())
    {
         mylist.append("1");
    }
    else
    {
         mylist.append("0");
    }
    if(ui->F_2_MIN2_selected->isChecked())
    {
         mylist.append("1");
    }
    else
    {
         mylist.append("0");
    }


    mylist.append(ui->a1->text());//6
    mylist.append(ui->b1->text());//7
    mylist.append(ui->a2->text());//8
    mylist.append(ui->b2->text());//9



    //mylist.append(ui->trigcomboBox->currentText());
    emit sendConfig(mylist);
}

