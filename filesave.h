#ifndef FILESAVE_H
#define FILESAVE_H
#include <QObject>
#include <qthread.h>
#include <qfile.h>
#include <qfiledialog.h>
#include <QTextStream>
#include <QDebug>
#include <QDateTime>

class filesave:public QThread
{
    Q_OBJECT
public:
    filesave();
public slots:
    void savecocnData(QVector <double>,QString);
    void saveORIGNData(QVector <double>,QVector <double>,QString);
};

#endif // FILESAVE_H
