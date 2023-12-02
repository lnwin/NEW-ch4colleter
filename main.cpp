#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    qRegisterMetaType<QList<QString>>( "QList<QString>" );
    qRegisterMetaType<QVector <double>>( "QVector <double>" );
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
