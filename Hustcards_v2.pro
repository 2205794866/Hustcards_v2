QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    add_money.cpp \
    canteen.cpp \
    card.cpp \
    cardmanager.cpp \
    consume.cpp \
    fail.cpp \
    logger.cpp \
    main.cpp \
    mainwindow.cpp \
    new_stu.cpp \
    operation.cpp \
    person.cpp \
    regex_search.cpp \
    search_result.cpp \
    search_stu.cpp \
    stu_info.cpp \
    succeed.cpp \
    time_set.cpp

HEADERS += \
    add_money.h \
    canteen.h \
    card.h \
    cardmanager.h \
    consume.h \
    fail.h \
    logger.h \
    mainwindow.h \
    new_stu.h \
    operation.h \
    person.h \
    regex_search.h \
    search_result.h \
    search_stu.h \
    std.h \
    stu_info.h \
    succeed.h \
    time_set.h

FORMS += \
    add_money.ui \
    consume.ui \
    fail.ui \
    mainwindow.ui \
    new_stu.ui \
    regex_search.ui \
    search_result.ui \
    search_stu.ui \
    stu_info.ui \
    succeed.ui \
    time_set.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
