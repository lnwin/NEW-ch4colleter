#include "mydatecard.h"

myDateCard::myDateCard()
{
  ADtimer =new QTimer(this);
  ADtimer->setInterval(1000);
  connect(ADtimer, SIGNAL(timeout()), this, SLOT(onTimeOut()));
  for(int i =0;i<500;i+=1)
  {
      localDataList_0.push_back(0);
      localDataList_1.push_back(0);
  }
}

void myDateCard::onTimeOut()
{
     myStartSample();
};

void myDateCard::timerTriger(bool myT)
{
    if(myT)
    {

       M3F20xm_InitFIFO(byDevIndex);
       if (M3F20xm_ADCStart(byDevIndex))
           {
               myADCCfg.dwCycleCnt = 0;
               myADCCfg.byTrigOptions |= 0x80;
               ADtimer->start();
           }

    }
    else
    {
        if (M3F20xm_ADCStop(byDevIndex))
            {

                myADCCfg.byTrigOptions &= 0x7F;
                ADtimer->stop();
                localDataList_0.clear();
                localDataList_1.clear();

            }

    }
}
void myDateCard::myInit()
{
    ADC_CONFIG tmpcfg;
    BYTE index;
    memcpy(&tmpcfg, &myADCCfg, sizeof(ADC_CONFIG));
//
  //  qDebug()<<tmpcfg.byADCOptions;

       // tmpcfg.w = 3072;
        tmpcfg.dwMaxCycles = 500;
        tmpcfg.wPeriod = 1000;
        tmpcfg.byADCOptions &=0xc8; //0xC8;
        index = 0<< 5;
        tmpcfg.byADCOptions += index;
        index = 1;//rangge
        index = index << 4;
        tmpcfg.byADCOptions += index;
        index = 0;//os
        tmpcfg.byADCOptions += index;
//      index = 0;//OS
//      tmpcfg.byADCOptions += index;
//      trigMode = 2;//trig mode  2=both
        index = 2;
        index+=1<<2;
        index+=0<<4;
        tmpcfg.byTrigOptions = index;
//      index = 0;
//      tmpcfg.byTrigOptions += index;
        if (M3F20xm_ADCSetConfig(byDevIndex, &tmpcfg))
        {

            memcpy(&myADCCfg, &tmpcfg, sizeof(ADC_CONFIG));
            if (myADCCfg.byADCOptions & 0x10)
                MaxVol = 10;
            else
                MaxVol = 5;
        }
        else
        {
            qDebug()<<("设置失败!");
        }
};
void myDateCard::myStartSample()
{
        M3F20xm_ADCStart(byDevIndex);
        if (M3F20xm_ADCStart(byDevIndex))
        {
            myADCCfg.dwCycleCnt = 0;
            myADCCfg.byTrigOptions |= 0x80;

        }

    // Delay_MSec(50);
    if(byDevIndex == 0xFF)
    {
       qDebug()<< "设备未连接!";
       return;
    }
       QList <double> after_s;
     //  after_s.reserve(500);
       QList <double> after_s1;
     //  after_s1.reserve(500);
       DWORD pdwRealSize = 0;//实际读取的数据长度
       byte lpBuffer[320000];//用来保存读取内容的缓存区
       // char Temp[200];
        WORD cycles;
        double realVol;
        double realVol_1;
        double realVol_2;
        //int i =0;
//         if (myADCCfg.byADCOptions & 0x10)
//                MaxVol = 10;
//                MaxVol = 5;
       QVector <double> originBuffer;
       QVector <double> originBuffer_1;
        if (M3F20xm_ReadFIFO(byDevIndex, lpBuffer, 320000, &pdwRealSize))
        {
            if (pdwRealSize > 0)
            {
              // qDebug()<<"pdwRealSize==="<<pdwRealSize;
                cycles = pdwRealSize / 16;
                for(int j = 0; j < cycles;j++)
                {

                    WORD byDataArray[8];
                    memcpy(byDataArray, &lpBuffer[j * 16], 16);

                   // for( int i=0;i<8;i++)
                   // {
                        if ((byDataArray[0] & 0x8000) == 0x8000)
                        {
                            byDataArray[0] = ~byDataArray[0];
                            //realVol = -1 * MaxVol * (code + 1) / 32768;
                            realVol = -1 * MaxVol * (byDataArray[0] + 1) / 32768;
                            //str.Format("%3.6f   ",realVol);
                            //str = String.Format("{0:0.000000}", realVol);

                        }
                        else
                        {
                            //realVol = MaxVol * (Sample[i] + 1) / 32768;
                            realVol = MaxVol * (byDataArray[0] + 1) / 32768;
                            //str = String.Format("{0:0.000000}", realVol);

                        }
                        originBuffer.push_back(realVol);
                         if ((byDataArray[1] & 0x8000) == 0x8000)
                         {
                             byDataArray[1] = ~byDataArray[1];
                             //realVol = -1 * MaxVol * (code + 1) / 32768;
                             realVol_1 = -1 * MaxVol * (byDataArray[1] + 1) / 32768;
                             //str.Format("%3.6f   ",realVol);
                             //str = String.Format("{0:0.000000}", realVol);

                         }
                         else
                         {
                             //realVol = MaxVol * (Sample[i] + 1) / 32768;
                             realVol_1 = MaxVol * (byDataArray[1] + 1) / 32768;
                             //str = String.Format("{0:0.000000}", realVol);

                         }
                          originBuffer_1.push_back(realVol_1);
                         if ((byDataArray[2] & 0x8000) == 0x8000)
                         {
                             byDataArray[2] = ~byDataArray[2];
                             //realVol = -1 * MaxVol * (code + 1) / 32768;
                             realVol_2 = -1 * MaxVol * (byDataArray[2] + 1) / 32768;
                             //str.Format("%3.6f   ",realVol);
                             //str = String.Format("{0:0.000000}", realVol);

                         }
                         else
                         {
                             //realVol = MaxVol * (Sample[i] + 1) / 32768;
                             realVol_2 = MaxVol * (byDataArray[2] + 1) / 32768;
                             //str = String.Format("{0:0.000000}", realVol);

                         }
                     //}



                }
                myADCCfg.dwCycleCnt += cycles;
                float akc=25.5677*realVol_2-23.43824;
                emit sendbar2main(akc);

                 //  qDebug()<<originBuffer_1.length();

                   if(ifcout&&ifMAX_MIN)
                   {

                         float COCN0;
                         float COCN1;
                       if(counTimer<coutTime)
                          {
                              for(int i =0;i<500;i+=1)
                              {
                                  localDataList_0[i]+=originBuffer[i];
                                  localDataList_1[i]+=originBuffer_1[i];
                              }
                              counTimer+=1;
                          }


                       else if(coutTime==0)
                       {

                               localDataList_0=originBuffer;
                               localDataList_1=originBuffer_1;

                       }
                       else
                       {

                           if(coutTime!=0)
                           {
                               for(int i =0;i<500;i+=1)
                               {
                                   localDataList_0[i]=(localDataList_0[i]/coutTime);
                                   localDataList_1[i]=(localDataList_1[i]/coutTime);
                               }
                           }

                           // =============================================================1



                                          double *MAX1B1=new double[max1_1_end-max1_1_start];
                                          double *MAX1B2=new double[max1_2_end-max1_2_start];
                                          double *MIN1B1=new double[min1_1_end-min1_1_start];
                                          double *MIN1B2=new double[min1_2_end-min1_2_start];
                                          for(int j=max1_1_start; j<max1_1_end;j++)
                                          {
                                                MAX1B1[j-max1_1_start]=localDataList_0[j];
                                          }
                                          for(int j=max1_2_start; j<max1_2_end;j++)
                                          {
                                                MAX1B2[j-max1_2_start]=localDataList_0[j];
                                          }
                                          for(int j=min1_1_start; j<min1_1_end;j++)
                                          {
                                                MIN1B1[j-min1_1_start]=localDataList_0[j];

                                          }
                                          for(int j=min1_2_start; j<min1_2_end;j++)
                                          {
                                                MIN1B2[j-min1_2_start]=localDataList_0[j];
                                          }
                                          Max_Min MN1_MAXB1;
                                          Max_Min MN1_MAXB2;
                                          Max_Min MN1_MINB1;
                                          Max_Min MN1_MINB2;

                                          MN1_MAXB1=coutMaxMin(MAX1B1,max1_1_end-max1_1_start);
                                          MN1_MAXB2=coutMaxMin(MAX1B2,max1_2_end-max1_2_start);
                                          MN1_MINB1=coutMaxMin(MIN1B1,min1_1_end-min1_1_start);
                                          MN1_MINB2=coutMaxMin(MIN1B2,min1_2_end-min1_2_start);



                                          if(F_1_MAX2_selected&&(!F_1_MIN2_selected))
                                          {
                                                double MAX=(MN1_MAXB1.Max+MN1_MAXB2.Max)/2;
                                                double MIN=MN1_MINB1.Min;
                                                double X =MAX-MIN;
                                                COCN0 = (a1*X)+b1;

                                          }
                                          if((!F_1_MAX2_selected)&&(F_1_MIN2_selected))
                                          {
                                                double MAX=MN1_MAXB1.Max;
                                                double MIN=(MN1_MINB1.Min+MN1_MINB1.Min)/2;
                                                double X =MAX-MIN;
                                                COCN0 = (a1*X)+b1;

                                          }




                  //=========================================================================================2

                                          double *MAX2B1=new double[max2_1_end-max2_1_start];
                                          double *MAX2B2=new double[max2_2_end-max2_2_start];
                                          double *MIN2B1=new double[min2_1_end-min2_1_start];
                                          double *MIN2B2=new double[min2_2_end-min2_2_start];
                                          for(int j=max2_1_start; j<max2_1_end;j++)
                                          {
                                                MAX2B1[j-max2_1_start]=localDataList_1[j];
                                          }
                                          for(int j=max2_2_start; j<max2_2_end;j++)
                                          {
                                                MAX2B2[j-max2_2_start]=localDataList_1[j];
                                          }
                                          for(int j=min2_1_start; j<min2_1_end;j++)
                                          {
                                                MIN2B1[j-min2_1_start]=localDataList_1[j];

                                          }
                                          for(int j=min2_2_start; j<min2_2_end;j++)
                                          {
                                                MIN2B2[j-min2_2_start]=localDataList_1[j];
                                          }
                                          Max_Min MN2_MAXB1;
                                          Max_Min MN2_MAXB2;
                                          Max_Min MN2_MINB1;
                                          Max_Min MN2_MINB2;

                                          MN2_MAXB1=coutMaxMin(MAX2B1,max2_1_end-max2_1_start);
                                          MN2_MAXB2=coutMaxMin(MAX2B2,max2_2_end-max2_2_start);
                                          MN2_MINB1=coutMaxMin(MIN2B1,min2_1_end-min2_1_start);
                                          MN2_MINB2=coutMaxMin(MIN2B2,min2_2_end-min2_2_start);



                                          if(F_2_MAX2_selected&&(!F_2_MIN2_selected))
                                          {
                                                double MAX=(MN2_MAXB1.Max+MN2_MAXB2.Max)/2;
                                                double MIN=MN2_MINB1.Min;
                                                double X =MAX-MIN;
                                                COCN1 = (a2*X)+b2;

                                          }
                                          if((!F_2_MAX2_selected)&&(F_2_MIN2_selected))
                                          {
                                                double MAX=MN2_MAXB1.Max;
                                                double MIN=(MN2_MINB1.Min+MN2_MINB1.Min)/2;
                                                double X =MAX-MIN;
                                                COCN1 = (a2*X)+b2;
                                          }


                                          QVector <double> myCOCN;
                                          double nowTime = QDateTime::currentDateTime().toMSecsSinceEpoch() / 1000.0;
                                          myCOCN.push_back (nowTime);
                                          myCOCN.push_back(COCN0);
                                          myCOCN.push_back(COCN1);

                                          emit sendCOCN2main(myCOCN);
                                          emit sendCOCN2Chart(myCOCN);
                                          emit saveCOCN(myCOCN,filepath);


                                          emit sendDate2Chart(localDataList_0,localDataList_1);
                                          emit saveoprigin(localDataList_0,localDataList_1,filepath);


                                          localDataList_0.clear();
                                          localDataList_1.clear();

                                          qDebug()<<" Clear here";
                                          for(int i =0;i<500;i+=1)
                                          {
                                              localDataList_0.push_back(0);
                                              localDataList_1.push_back(0);
                                          }

                                           counTimer=0;
                            }

                       }
                   else if(ifcout&&!ifMAX_MIN)
                   {
                       if(counTimer<coutTime)
                          {
                              for(int i =0;i<500;i+=1)
                              {
                                  localDataList_0[i]+=originBuffer[i];
                                  localDataList_1[i]+=originBuffer_1[i];
                              }
                              counTimer+=1;
                          }

                       else if(coutTime==0)
                       {

                               localDataList_0=originBuffer;
                               localDataList_1=originBuffer_1;

                       }

                       else
                       {

                           if(coutTime!=0)
                           {
                               for(int i =0;i<500;i+=1)
                               {
                                   localDataList_0[i]=(localDataList_0[i]/coutTime);
                                   localDataList_1[i]=(localDataList_1[i]/coutTime);
                               }
                           }

                            emit sendDate2Chart(localDataList_0,localDataList_1);
                            emit saveoprigin(localDataList_0,localDataList_1,filepath);
                            localDataList_0.clear();
                            localDataList_1.clear();
                            for(int i =0;i<500;i+=1)
                            {
                                localDataList_0.push_back(0);
                                localDataList_1.push_back(0);
                            }
                            counTimer=0;

                       }
                   }
                   else if(!ifcout&&ifMAX_MIN)
                   {





                       emit sendDate2Chart(originBuffer,originBuffer_1);

                       emit saveoprigin(originBuffer,originBuffer_1,filepath);

                       localDataList_0=originBuffer;
                       localDataList_1=originBuffer_1;

                       float COCN0;
                       float COCN1;
                       double *MAX1B1=new double[max1_1_end-max1_1_start];
                       double *MAX1B2=new double[max1_2_end-max1_2_start];
                       double *MIN1B1=new double[min1_1_end-min1_1_start];
                       double *MIN1B2=new double[min1_2_end-min1_2_start];
                       for(int j=max1_1_start; j<max1_1_end;j++)
                       {
                            MAX1B1[j-max1_1_start]=localDataList_0[j];
                       }
                       for(int j=max1_2_start; j<max1_2_end;j++)
                       {
                            MAX1B2[j-max1_2_start]=localDataList_0[j];
                       }
                       for(int j=min1_1_start; j<min1_1_end;j++)
                       {
                            MIN1B1[j-min1_1_start]=localDataList_0[j];

                       }
                       for(int j=min1_2_start; j<min1_2_end;j++)
                       {
                            MIN1B2[j-min1_2_start]=localDataList_0[j];
                       }
                       Max_Min MN1_MAXB1;
                       Max_Min MN1_MAXB2;
                       Max_Min MN1_MINB1;
                       Max_Min MN1_MINB2;

                       MN1_MAXB1=coutMaxMin(MAX1B1,max1_1_end-max1_1_start);
                       MN1_MAXB2=coutMaxMin(MAX1B2,max1_2_end-max1_2_start);
                       MN1_MINB1=coutMaxMin(MIN1B1,min1_1_end-min1_1_start);
                       MN1_MINB2=coutMaxMin(MIN1B2,min1_2_end-min1_2_start);



                       if(F_1_MAX2_selected&&(!F_1_MIN2_selected))
                       {
                            double MAX=(MN1_MAXB1.Max+MN1_MAXB2.Max)/2;
                            double MIN=MN1_MINB1.Min;
                            double X =MAX-MIN;
                            COCN0 = (a1*X)+b1;
                       }
                       if((!F_1_MAX2_selected)&&(F_1_MIN2_selected))
                       {
                            double MAX=MN1_MAXB1.Max;
                            double MIN=(MN1_MINB1.Min+MN1_MINB1.Min)/2;
                            double X =MAX-MIN;
                            COCN0 = (a1*X)+b1;
                       }




                       //=========================================================================================2

                       double *MAX2B1=new double[max2_1_end-max2_1_start];
                       double *MAX2B2=new double[max2_2_end-max2_2_start];
                       double *MIN2B1=new double[min2_1_end-min2_1_start];
                       double *MIN2B2=new double[min2_2_end-min2_2_start];
                       for(int j=max2_1_start; j<max2_1_end;j++)
                       {
                            MAX2B1[j-max2_1_start]=localDataList_1[j];
                       }
                       for(int j=max2_2_start; j<max2_2_end;j++)
                       {
                            MAX2B2[j-max2_2_start]=localDataList_1[j];
                       }
                       for(int j=min2_1_start; j<min2_1_end;j++)
                       {
                            MIN2B1[j-min2_1_start]=localDataList_1[j];

                       }
                       for(int j=min2_2_start; j<min2_2_end;j++)
                       {
                            MIN2B2[j-min2_2_start]=localDataList_1[j];
                       }
                       Max_Min MN2_MAXB1;
                       Max_Min MN2_MAXB2;
                       Max_Min MN2_MINB1;
                       Max_Min MN2_MINB2;

                       MN2_MAXB1=coutMaxMin(MAX2B1,max2_1_end-max2_1_start);
                       MN2_MAXB2=coutMaxMin(MAX2B2,max2_2_end-max2_2_start);
                       MN2_MINB1=coutMaxMin(MIN2B1,min2_1_end-min2_1_start);
                       MN2_MINB2=coutMaxMin(MIN2B2,min2_2_end-min2_2_start);



                       if(F_2_MAX2_selected&&(!F_2_MIN2_selected))
                       {
                            double MAX=(MN2_MAXB1.Max+MN2_MAXB2.Max)/2;
                            double MIN=MN2_MINB1.Min;
                            double X =MAX-MIN;
                            COCN1 = (a2*X)+b2;
                       }
                       if((!F_2_MAX2_selected)&&(F_2_MIN2_selected))
                       {
                            double MAX=MN2_MAXB1.Max;
                            double MIN=(MN2_MINB1.Min+MN2_MINB1.Min)/2;
                            double X =MAX-MIN;
                            COCN1 = (a2*X)+b2;
                       }


                       QVector <double> myCOCN;
                       double nowTime = QDateTime::currentDateTime().toMSecsSinceEpoch() / 1000.0;
                       myCOCN.push_back (nowTime);
                       myCOCN.push_back(COCN0);
                       myCOCN.push_back(COCN1);
                       emit sendCOCN2main(myCOCN);
                       emit sendCOCN2Chart(myCOCN);
                       emit saveCOCN(myCOCN,filepath);

                   }
                   else
                   {

//
                             emit sendDate2Chart(originBuffer,originBuffer_1);

                             emit saveoprigin(originBuffer,originBuffer_1,filepath);
                            // originBuffer.clear();
                            // originBuffer_1.clear();
                   }


            }
        }
        else
                {
                   qDebug()<<"采样读数据失败!";
                }

        if (myADCCfg.dwCycleCnt == myADCCfg.dwMaxCycles)
           {
             myADCCfg.byTrigOptions &= 0x7F;
            // ADtimer->stop();
           }

//        if(M3F20xm_ADCStop(byDevIndex))
//           {
//                   myADCCfg.byTrigOptions &= 0x7F;
//           }

};
void myDateCard::connectDevice()
{

    char serial[15] = { 0 };
     BYTE byVerified;
     if (byDevIndex != 0xFF)
     {
         if (myADCCfg.byTrigOptions & 0x80)   //trig mode
         {
             myADCCfg.byTrigOptions &= 0x7F;

         }
         if (M3F20xm_CloseDevice(byDevIndex) == false)
         {
             qDebug()<<("关闭设备失败!");

         }
         else
         {

           byDevIndex = 0xFF;
            emit connectsuccess(false);
         }

     }
     else
     {
         byDevIndex = M3F20xm_OpenDevice();
         if (byDevIndex == 0xFF)
         {
            qDebug()<<("打开设备失败!");


         }
         else
         {

             if (!M3F20xm_Verify(byDevIndex, &byVerified))
             {
                 qDebug()<<("设备认证失败!");
                 M3F20xm_CloseDevice(byDevIndex);
                 byDevIndex = 0xFF;

             }

             if (byVerified)
             {
                 M3F20xm_ADCGetConfig(byDevIndex, &myADCCfg);
                 if (myADCCfg.byADCOptions & 0x10)
                     MaxVol = 10;
                 else
                     MaxVol = 5;
                  myInit();
                 qDebug()<<"设备已链接"<<QThread::currentThread();
                // qDebug()<<mainport->isOpen();
                  M3F20xm_GetSerialNo(byDevIndex, serial);
                  emit connectsuccess(true);
             }


         }
     }





};
Max_Min myDateCard::coutMaxMin(double *dataIn,double n)
{
    Max_Min mn;
    mn.Max=dataIn[0];
    mn.Min=dataIn[0];
    for(int i=0;i<n;i++)
    {

        if(dataIn[i]> mn.Max)
        {
           mn.Max =dataIn[i];
         //qDebug()<<Max;
        }
        if(dataIn[i]<mn.Min)
        {
          mn.Min=dataIn[i];
        }

    }
    return mn;

}
void myDateCard::receiveConfig(QList<QString> list)
{


    filepath=list.at(0);
    coutTime=list.at(1).toInt();
    max1_1_start=list.at(2).split("/").at(0).toInt();
    max1_1_end=list.at(2).split("/").at(1).toInt();

    max1_2_start=list.at(3).split("/").at(0).toInt();
    max1_2_end=list.at(3).split("/").at(1).toInt();

    min1_1_start=list.at(4).split("/").at(0).toInt();
    min1_1_end=list.at(4).split("/").at(1).toInt();
    min1_2_start=list.at(5).split("/").at(0).toInt();
    min1_2_end=list.at(5).split("/").at(1).toInt();

    max2_1_start=list.at(6).split("/").at(0).toInt();
    max2_1_end=list.at(6).split("/").at(1).toInt();

    max2_2_start=list.at(7).split("/").at(0).toInt();
    max2_2_end=list.at(7).split("/").at(1).toInt();

    min1_1_start=list.at(8).split("/").at(0).toInt();
    min1_1_end=list.at(8).split("/").at(1).toInt();
    min1_2_start=list.at(9).split("/").at(0).toInt();
    min1_2_end=list.at(9).split("/").at(1).toInt();

    if(list.at(10)=="1")
    {
        ifcout=true;
    }
    else
    {
        ifcout=false;
    }
    if(list.at(11)=="1")
    {
        ifMAX_MIN=true;
    }
    else
    {
        ifMAX_MIN=false;
    }

    if(list.at(12)=="1")
    {
        F_1_MAX1_selected=true;
    }
    else
    {
        F_1_MAX1_selected=false;
    }

    if(list.at(13)=="1")
    {
        F_1_MAX2_selected=true;
    }
    else
    {
        F_1_MAX2_selected=false;
    }

    if(list.at(14)=="1")
    {
        F_1_MIN1_selected=true;
    }
    else
    {
        F_1_MIN1_selected=false;
    }

    if(list.at(15)=="1")
    {
        F_1_MIN2_selected=true;
    }
    else
    {
        F_1_MIN2_selected=false;
    }

    if(list.at(16)=="1")
    {
        F_2_MAX1_selected=true;
    }
    else
    {
        F_2_MAX1_selected=false;
    }
    if(list.at(17)=="1")
    {
        F_2_MAX2_selected=true;
    }
    else
    {
        F_2_MAX2_selected=false;
    }
    if(list.at(18)=="1")
    {
        F_2_MIN1_selected=true;
    }
    else
    {
        F_2_MIN1_selected=false;
    }
    if(list.at(19)=="1")
    {
        F_2_MIN2_selected=true;
    }
    else
    {
        F_2_MIN2_selected=false;
    }
    a1=list.at(20).toDouble();
    b1=list.at(21).toDouble();
    a2=list.at(22).toDouble();
    b2=list.at(23).toDouble();



    myInit();

};
void myDateCard::Delay_MSec(unsigned int msec)
{

        QTime _Timer = QTime::currentTime().addMSecs(msec);

        while( QTime::currentTime() < _Timer )

        QCoreApplication::processEvents(QEventLoop::AllEvents, 1);

};


