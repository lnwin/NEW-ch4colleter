#include "mychart.h"
#include <QMenu>
#include <QAction>
#include <QMenuBar>
#include <QVBoxLayout>
#include <QDebug>
#include <QPoint>
mychart::mychart(Ui::MainWindow *myui)
{
    myUI=myui;




}


void mychart::Chart_Cinit()
{


   myUI->myQcustomCHart ->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                   QCP::iSelectLegend | QCP::iSelectPlottables);
   QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);



   dateTicker->setDateTimeFormat("hh:mm:ss");
   myUI->myQcustomCHart->xAxis->setTicker(dateTicker);
  // ui.customPlot->xAxis->setRange(-100, 100);
   myUI->myQcustomCHart->yAxis->setRange(-100, 100);

   myUI->myQcustomCHart->axisRect()->setupFullAxesBox();
  myUI->myQcustomCHart->plotLayout()->insertRow(0);
   QCPTextElement *title = new QCPTextElement(myUI->myQcustomCHart, "气体浓度曲线", QFont("sans", 17, QFont::Bold));
   myUI->myQcustomCHart->plotLayout()->addElement(0, 0, title);
   myUI->myQcustomCHart->xAxis->setLabel("时间");
   myUI->myQcustomCHart->yAxis->setLabel("浓度（PPM）");
   myUI->myQcustomCHart->legend->setVisible(true);
//    QLinearGradient plotGradient;
//  //  plotGradient.setStart(0, 0);
//   // plotGradient.setFinalStop(0, 350);
//   // plotGradient.setColorAt(0, QColor(80, 80, 80));
//    plotGradient.setColorAt(1, QColor(50, 50, 50));
//    ui.customPlot->setBackground(plotGradient);
   QFont legendFont("Times", 10, QFont::Bold);
   legendFont.setPointSize(10);
   myUI->myQcustomCHart->legend->setFont(legendFont);
   myUI->myQcustomCHart->legend->setSelectedFont(legendFont);
   myUI->myQcustomCHart->legend->setSelectableParts(QCPLegend::spItems);
   myUI->myQcustomCHart->addGraph();
   myUI->myQcustomCHart->graph(0)->setName("气体浓度-1");
   QPen graphPen;
   graphPen.setColor(QColor(16,177,171));
   graphPen.setWidthF(2);
   myUI->myQcustomCHart->graph(0)->setPen(graphPen);



   QFont legendFont1("Times", 10, QFont::Bold);
   legendFont1.setPointSize(10);
   myUI->myQcustomCHart->legend->setFont(legendFont1);
   myUI->myQcustomCHart->legend->setSelectedFont(legendFont1);
   myUI->myQcustomCHart->legend->setSelectableParts(QCPLegend::spItems);
   myUI->myQcustomCHart->addGraph();
   myUI->myQcustomCHart->graph(1)->setName("气体浓度-2");
   QPen graphPen1;
   graphPen1.setColor(QColor(16,17,171));
   graphPen1.setWidthF(2);
   myUI->myQcustomCHart->graph(1)->setPen(graphPen1);

  // Chart_Mupdata(ui);
   myUI->myQcustomCHart->rescaleAxes();

}
void mychart::Chart_Origininit()
{
    myUI->myOriginChart->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(myUI->myOriginChart, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenuRequest(QPoint)));

    myUI->myOriginChart ->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                    QCP::iSelectLegend | QCP::iSelectPlottables);
   // QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);
   // dateTicker->setDateTimeFormat("hh:mm:ss");
   // myUI->myOriginChart->xAxis->setTicker(dateTicker);
    myUI->myOriginChart->xAxis->setRange(0, 500);
    myUI->myOriginChart->yAxis->setRange(-100, 100);
    myUI->myOriginChart->yAxis2->setVisible(true);
    myUI->myOriginChart->yAxis2->setRange(-10, 10);
   // myUI->myOriginChart->yAxis2

   // myUI->myOriginChart->axisRect()

    myUI->myOriginChart->plotLayout()->insertRow(0);
    QCPTextElement *title = new QCPTextElement(myUI->myOriginChart, "原始数据曲线", QFont("sans", 17, QFont::Bold));
    myUI->myOriginChart->plotLayout()->addElement(0, 0, title);
    myUI->myOriginChart->xAxis->setLabel("数据个数");
    myUI->myOriginChart->yAxis->setLabel("1通道原始值");
    myUI->myOriginChart->yAxis2->setLabel("2通道原始值");
    myUI->myOriginChart->legend->setVisible(true);
 //    QLinearGradient plotGradient;
 //  //  plotGradient.setStart(0, 0);
 //   // plotGradient.setFinalStop(0, 350);
 //   // plotGradient.setColorAt(0, QColor(80, 80, 80));
 //    plotGradient.setColorAt(1, QColor(50, 50, 50));
 //    ui.customPlot->setBackground(plotGradient);
    QFont legendFont("Times", 10, QFont::Bold);
    legendFont.setPointSize(10);
    myUI->myOriginChart->legend->setFont(legendFont);
    myUI->myOriginChart->legend->setSelectedFont(legendFont);
    myUI->myOriginChart->legend->setSelectableParts(QCPLegend::spItems);
    myUI->myOriginChart->addGraph();
    myUI->myOriginChart->graph(0)->setName("1通道原始数据");
    QPen graphPen;
    graphPen.setColor(QColor(161,17,171));
    graphPen.setWidthF(2);
    myUI->myOriginChart->graph(0)->setPen(graphPen);
   // myUI->myOriginChart->addGraph();


    myUI->myOriginChart->addGraph( myUI->myOriginChart->xAxis,myUI->myOriginChart->yAxis2);
    myUI->myOriginChart->graph(1)->setName("2通道原始数据");
    QPen graphPen1;
    graphPen1.setColor(QColor(51,127,21));
    graphPen1.setWidthF(2);
    myUI->myOriginChart->graph(1)->setPen(graphPen1);
   // Chart_Mupdata(ui);
    myUI->myOriginChart->rescaleAxes();

}

void mychart::Chart_Cupdata()
{

};

void mychart::receiveDate2Chart(QVector <double> L1,QVector <double> L2)
{
  //  qDebug()<<"L1==="<<L1.length();
   // qDebug()<<"L2==="<<L2.length();

    QVector<double> MYX(L1.length());

    for(int i=0;i<L1.length();i++)
    {
        MYX[i] =i;
    }
 //  myUI->myOriginChart->clearGraphs();

   myUI->myOriginChart->graph(0)->setData(MYX,L1);

   myUI->myOriginChart->graph(1)->setData(MYX,L2);
   myUI->myOriginChart->rescaleAxes();
   myUI->myOriginChart->replot();

};
void mychart::receiveCOCN2Chart(QVector <double>mycocn)
{


    double time=mycocn[0];
    double data1=mycocn[1];
    double data2=mycocn[2];
    qDebug()<<"data1"<<data1;

    if(COCNd1.length()>20)
    {
        COCNt.removeAt(0);
        COCNd1.removeAt(0);
        COCNd2.append(0);
        COCNt.append(time);
        COCNd1.append(data1);
        COCNd2.append(data2);
    }
    else
    {
        COCNt.append(time);
        COCNd1.append(data1);
        COCNd2.append(data2);
    }

     myUI->myQcustomCHart->graph(0)->setData(COCNt,COCNd1);
     myUI->myQcustomCHart->graph(1)->setData(COCNt,COCNd2);
     myUI->myQcustomCHart->rescaleAxes();
     myUI->myQcustomCHart->replot();


}


void mychart::contextMenuRequest(QPoint pos)
{
    QMenu *menu = new QMenu(myUI->myOriginChart);
    menu->setAttribute(Qt::WA_DeleteOnClose);

    double legendCounts = myUI->myOriginChart->legend->selectTest(pos, false);
    double graphCounts = myUI->myOriginChart->graph()->selectTest(pos,false);

    //图例菜单
    if (( legendCounts >= 0) || ( graphCounts >= 0))
    {
        menu->addAction("显示", this, SLOT(showGraph()));
        menu->addAction("隐藏", this, SLOT(hideGraph()));
    }

    menu->popup(myUI->myOriginChart->mapToGlobal(pos));
}

void mychart::showGraph()
{
    for (int i=0; i<myUI->myOriginChart->graphCount(); ++i)
    {
        QCPGraph *graphItem = myUI->myOriginChart->graph(i);
        QCPPlottableLegendItem *item =myUI->myOriginChart->legend->itemWithPlottable(graphItem);
        if (item->selected())
        {
            graphItem->setVisible(true);
            //qDebug()<<"graphItem->selected()"<<graphItem->selected();
        }
    }
    myUI->myOriginChart->replot();


}

void mychart::hideGraph()
{
    for (int i=0; i< myUI->myOriginChart->graphCount(); ++i)
    {
        QCPGraph *graphItem = myUI->myOriginChart->graph(i);

        QCPPlottableLegendItem *item =myUI->myOriginChart->legend->itemWithPlottable(graphItem);
        if (item->selected())
        {
            graphItem->setVisible(false);
            //qDebug()<<"graphItem->selected()"<<graphItem->selected();
        }
    }
   myUI->myOriginChart->replot();

}

void mychart::on_writeconfig_clicked()
{

}

