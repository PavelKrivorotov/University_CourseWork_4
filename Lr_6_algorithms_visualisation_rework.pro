QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    animations/additemanimation.cpp \
    animations/algorithmanimation.cpp \
    animations/balancetreeanimation.cpp \
    animations/baseanimation.cpp \
    animations/differenceheightanimation.cpp \
    animations/getitemanimation.cpp \
    animations/removeitemanimation.cpp \
    main.cpp \
    mainwindow.cpp \
    dialogs/confirmdialog.cpp \
    graphics/graphicbinarytree.cpp \
    graphics/graphicnode.cpp


HEADERS += \
    animations/additemanimation.h \
    animations/algorithmanimation.h \
    animations/balancetreeanimation.h \
    animations/baseanimation.h \
    animations/differenceheightanimation.h \
    animations/getitemanimation.h \
    animations/removeitemanimation.h \
    mainwindow.h \
    dialogs/confirmdialog.h \
    graphics/graphicbinarytree.h \
    graphics/graphicnode.h

FORMS += \
    mainwindow.ui \
    dialogs/confirmdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
