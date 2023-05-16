#include "filesave.h"

filesave::filesave()
{

}


void filesave::savecocnData(QVector <double>cocn,QString fp)
{
     QDateTime time =QDateTime::currentDateTime();
     QString filename =time.toString("yyyy-MM-dd")+"_COCN_DATA.txt";
     QString COCNpATH;
     COCNpATH=fp+"/COCN/";
     filename=COCNpATH+filename;
     QFile datafile(filename);
     QTextStream stream(&datafile);

     qDebug()<<"save    cocn======="<<cocn;
     if(!datafile.exists())
     {
        QDir *path =new QDir;
        path->mkdir(COCNpATH);
        datafile.open(QIODevice::WriteOnly | QIODevice::Text);

            stream<<time.toString("hh:mm:ss")<<"\t"<<cocn[1] <<"\t"<<cocn[2]<<"\n";


     }
     else
     {
           datafile.open(QIODevice::WriteOnly | QIODevice::Text|QIODevice::Append);
           stream<<time.toString("hh:mm:ss")<<"\t"<<cocn[1]<<"\t"<<cocn[2]<<"\n";

     }
     datafile.close();


}
void filesave::saveORIGNData(QVector <double>origidata_0,QVector <double>origidata_1,QString fp)
{
     QDateTime time =QDateTime::currentDateTime();
     QString filename1 =time.toString("yyyy-MM-dd")+"_origin_DATA.txt";
     QString COCNpATH1;
     COCNpATH1=fp+"/ORIGIN/";
     filename1=COCNpATH1+filename1;

     QFile cloudfile(filename1);
     QTextStream stream1(&cloudfile);
     if(!cloudfile.exists())

             {
                  QDir *folder = new QDir;
                  folder->mkdir(COCNpATH1);
                  cloudfile.open(QIODevice::WriteOnly | QIODevice::Text);
                  for( int i=0;i<origidata_0.length(); i++)
                  {
                       stream1<< time.toString("hh:mm:ss")<<"\t"<<origidata_0[i]<<"\t"<<origidata_1[i]<<"\n";

                  }

              }
     else
     {
         cloudfile.open(QIODevice::WriteOnly | QIODevice::Text|QIODevice::Append);
         for( int i=0;i<origidata_0.length(); i++)
         {
               stream1<< time.toString("hh:mm:ss")<<"\t"<<origidata_0[i]<<"\t"<<origidata_1[i]<<"\n";

         }

     }
     cloudfile.close();

}
