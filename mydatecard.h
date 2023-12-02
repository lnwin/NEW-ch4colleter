#ifndef MYDATECARD_H
#define MYDATECARD_H

#include <QObject>
#include <QThread>
#include <ad7606.h>
#include <QDebug>
#include <QTimer>
#include <QMetaType>
#include <QDateTime>
#include <QCoreApplication>
#include <QMessageBox>
struct Max_Min
{

    double Max;
    double Min;

};
Q_DECLARE_METATYPE(Max_Min);
class myDateCard : public QThread
{
    Q_OBJECT
public:
    explicit myDateCard();


public slots:

    void myInit();
    void myStartSample();
    void connectDevice();
    void onTimeOut();
    void timerTriger(bool);
    void receiveConfig(QList<QString>);
signals:

    void sendDate2Chart(QVector <double>,QVector <double>);
    void sendCOCN2Chart(QVector <double>);
    void sendbar2main(float);
    void sendCOCN2main(QVector<double>);

    void saveCOCN(QVector <double>,QString);
    void saveoprigin(QVector <double>,QVector <double>,QString);
    void savePressData(float,QString);
    void connectsuccess(bool);

private:
    //==========新采集卡
    BYTE byDevIndex =0xFF;
    DWORD dwReadCycle;
    ADC_CONFIG myADCCfg;
    bool bHexDisplay;
    float MaxVol;

    QTimer *ADtimer ;
    Max_Min coutMaxMin(double*,double);

    int coutTime=0;
    int max1_1_start=100;
    int max1_1_end=200;
    int max1_2_start=100;
    int max1_2_end=200;
    int min1_1_start=200;
    int min1_1_end=300;
    int min1_2_start=300;
    int min1_2_end=400;
    int max2_1_start=200;
    int max2_1_end=300;
    int max2_2_start=200;
    int max2_2_end=300;
    int min2_1_start=300;
    int min2_1_end=400;
    int min2_2_start=400;
    int min2_2_end=500;

    bool ifcout=false;
    int counTimer=0;
    bool ifMAX_MIN=false;

     bool F_1_MAX1_selected=false;
     bool F_1_MAX2_selected=false;
     bool F_1_MIN1_selected=false;
     bool F_1_MIN2_selected=false;

     bool F_2_MAX1_selected=false;
     bool F_2_MAX2_selected=false;
     bool F_2_MIN1_selected=false;
     bool F_2_MIN2_selected=false;


    float a1,b1,a2,b2;

    QString filepath="C:/DATA";
    QVector <double> originBuffer;
    QVector <double> originBuffer_1;
    QVector <double> localDataList_0;
    QVector <double> localDataList_1;

    double localConut_0=0;
    double localConut_1=0;

    int trigMode=0;

    void Delay_MSec(unsigned int msec);

};

#endif // MYDATECARD_H
