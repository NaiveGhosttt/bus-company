QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    a_bus.cpp \
    add_a_bus_dialog.cpp \
    infotable.cpp \
    main.cpp \
    mainwindow.cpp \
    passengerlist_dialog.cpp \
    readonlydelegate.cpp \
    refund_dialog.cpp \
    sale.cpp \
    sale_dialog.cpp \
    ticketleft_dialog.cpp

HEADERS += \
    a_bus.h \
    add_a_bus_dialog.h \
    infotable.h \
    mainwindow.h \
    passengerlist_dialog.h \
    readonlydelegate.h \
    refund_dialog.h \
    sale.h \
    sale_dialog.h \
    ticketleft_dialog.h

FORMS += \
    add_a_bus_dialog.ui \
    mainwindow.ui \
    passengerlist_dialog.ui \
    refund_dialog.ui \
    sale_dialog.ui \
    ticketleft_dialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
