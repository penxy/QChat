QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
INCLUDEPATH += /home/pxy/QT_Pro/Test/Dialog
INCLUDEPATH += /home/pxy/QT_Pro/Test/Config
LIBS += -L/path/to/jsoncpp/lib -ljsoncpp



# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    DiaLogCpp/confirm.cpp \
    DiaLogCpp/f_add.cpp \
    DiaLogCpp/f_beadd.cpp \
    DiaLogCpp/f_findid.cpp \
    DiaLogCpp/f_talk.cpp \
    DiaLogCpp/login.cpp \
    Log.cpp \
    User.cpp \
    main.cpp \
    tool.cpp \
    widget.cpp

HEADERS += \
    Config/CQSigconfig.h \
    Config/LimitConfig.h \
    Dialog/confirm.h \
    Dialog/f_add.h \
    Dialog/f_beadd.h \
    Dialog/f_findid.h \
    Dialog/f_talk.h \
    Dialog/login.h \
    Log.h \
    User.h \
    tool.h \
    widget.h

FORMS += \
    confirm.ui \
    f_add.ui \
    f_beadd.ui \
    f_findid.ui \
    f_talk.ui \
    login.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
