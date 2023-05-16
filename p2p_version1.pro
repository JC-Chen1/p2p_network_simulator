QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    clientnode.cpp \
    connection.cpp \
    connectiongraph.cpp \
    customer.cpp \
    datablock.cpp \
    event.cpp \
    infowidget.cpp \
    intro.cpp \
    main.cpp \
    mainwindow.cpp \
    node.cpp \
    playablesegment.cpp \
    presentationwidget.cpp \
    servernode.cpp \
    total.cpp \
    voronoi.cpp

HEADERS += \
    clientnode.h \
    connection.h \
    connectiongraph.h \
    customer.h \
    datablock.h \
    event.h \
    infowidget.h \
    intro.h \
    mainwindow.h \
    node.h \
    playablesegment.h \
    presentationwidget.h \
    servernode.h \
    total.h \
    voronoi.h

FORMS += \
    infowidget.ui \
    intro.ui \
    mainwindow.ui \
    presentationwidget.ui \
    total.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
