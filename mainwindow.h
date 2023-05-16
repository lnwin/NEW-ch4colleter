#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <mychart.h>
#include <mydatecard.h>
#include <filesave.h>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_connectDev_clicked();

    void on_startSample_clicked();

  //  void on_setConfig_clicked();

    void on_pushButton_fileselect_clicked();

    void on_writeconfig_clicked();

    void openlock(bool);

public slots:
    void receiveBar(float);

    void receiveCOCN2main(QVector<double>);

    void  myMoveEvent(QMouseEvent*);
signals:

    void connectD();
    void startSamTimer(bool);
    void sendConfig(QList<QString>);

private:
    Ui::MainWindow *ui;
    myDateCard *mpDataCard;
    mychart *mpChart;
    filesave *myfilesave;

    bool isSampling=false;
    bool setLocked=true;

    bool checkSampleFlag();

};
#endif // MAINWINDOW_H
