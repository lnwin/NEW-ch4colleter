#ifndef MYCHART_H
#define MYCHART_H

#include <QObject>
#include <QThread>
#include <ui_mainwindow.h>
class mychart :public QThread
{
    Q_OBJECT
public:
    mychart(Ui::MainWindow *myui);

    void Chart_Cinit();
    void Chart_Origininit();
    void Chart_Cupdata();

    Ui::MainWindow * myUI;


 public slots:
    void receiveDate2Chart(QVector <double>,QVector <double>);
    void receiveCOCN2Chart(QVector <double>);
    void contextMenuRequest(QPoint pos);
    void showGraph();
        // 被选中的曲线隐藏
    void hideGraph();
private slots:
    void on_writeconfig_clicked();
 //  void on_pushButton_fileselect_clicked();


private:
    QVector<double> COCNt,COCNd1,COCNd2;

    bool ishow_0=true;
    bool ishow_1=true;

};

#endif // MYCHART_H
