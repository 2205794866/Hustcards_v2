QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    card.cpp \
    cardmanager.cpp \
    fail.cpp \
    main.cpp \
    mainwindow.cpp \
    person.cpp \
    search_stu.cpp \
    stu_info.cpp \
    succeed.cpp

HEADERS += \
    card.h \
    cardmanager.h \
    fail.h \
    mainwindow.h \
    person.h \
    search_stu.h \
    std.h \
    stu_info.h \
    succeed.h

FORMS += \
    fail.ui \
    mainwindow.ui \
    search_stu.ui \
    stu_info.ui \
    succeed.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
