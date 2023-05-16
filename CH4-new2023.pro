QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

greaterThan(QT_MAJOR_VERSION, 4): CONFIG += c++11
lessThan(QT_MAJOR_VERSION, 5): QMAKE_CXXFLAGS += -std=c++11
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    filesave.cpp \
    main.cpp \
    mainwindow.cpp \
    mychart.cpp \
    mydatecard.cpp \
    qcustomplot.cpp

HEADERS += \
    filesave.h \
    mainwindow.h \
    mychart.h \
    mydatecard.h \
    qcustomplot.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lnclude/ -lad7606
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lnclude/ -lad7606d

INCLUDEPATH += $$PWD/lnclude
DEPENDPATH += $$PWD/lnclude

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/include/ -lad7606
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/include/ -lad7606d

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include
