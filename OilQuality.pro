QT       += core gui
QT       += serialport
QT       += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    appdata.cpp \
    btnswich.cpp \
    cmdmanager.cpp \
    dataserialtask.cpp \
    dlgautoresult.cpp \
    dlgclean.cpp \
    dlgdebug.cpp \
    dlgdeviceajust.cpp \
    dlginfo.cpp \
    dlglightswitch.cpp \
    dlgmaintain.cpp \
    dlgmaintaindevice.cpp \
    dlgmaintainmirror.cpp \
    dlgmdjcalc.cpp \
    dlgmeasure.cpp \
    dlgmeasure2.cpp \
    dlgmeasureinfo.cpp \
    dlgmeasurepreset.cpp \
    dlgmeasuresetting.cpp \
    dlgmeasurestart.cpp \
    dlgmeasurex.cpp \
    dlgmirrorsetting.cpp \
    dlgnumpad.cpp \
    dlgpanel.cpp \
    dlgpanneldate.cpp \
    dlgpasue.cpp \
    dlgpositionsetting.cpp \
    dlgresult.cpp \
    dlgresults.cpp \
    dlgsamplecell.cpp \
    dlgselfcheck.cpp \
    dlgsetup.cpp \
    dlgshutdown.cpp \
    dlgsysinfo.cpp \
    dlgsyssetting.cpp \
    dlgtemperaturesetting.cpp \
    dlgtimesetting.cpp \
    dlgupdate.cpp \
    dlgwash.cpp \
    main.cpp \
    thdserialtask.cpp \
    threadcheckstate.cpp \
    threadcmd.cpp \
    threadcommcmd.cpp \
    threadreadinfo.cpp \
    threadserialworker.cpp \
    widget.cpp \
    wndprogress.cpp \
    xchart.cpp

HEADERS += \
    DataInfo.h \
    appdata.h \
    btnswich.h \
    cmdmanager.h \
    dataserialtask.h \
    dlgautoresult.h \
    dlgclean.h \
    dlgdebug.h \
    dlgdeviceajust.h \
    dlginfo.h \
    dlglightswitch.h \
    dlgmaintain.h \
    dlgmaintaindevice.h \
    dlgmaintainmirror.h \
    dlgmdjcalc.h \
    dlgmeasure.h \
    dlgmeasure2.h \
    dlgmeasureinfo.h \
    dlgmeasurepreset.h \
    dlgmeasuresetting.h \
    dlgmeasurestart.h \
    dlgmeasurex.h \
    dlgmirrorsetting.h \
    dlgnumpad.h \
    dlgpanel.h \
    dlgpanneldate.h \
    dlgpasue.h \
    dlgpositionsetting.h \
    dlgresult.h \
    dlgresults.h \
    dlgsamplecell.h \
    dlgselfcheck.h \
    dlgsetup.h \
    dlgshutdown.h \
    dlgsysinfo.h \
    dlgsyssetting.h \
    dlgtemperaturesetting.h \
    dlgtimesetting.h \
    dlgupdate.h \
    dlgwash.h \
    inc.h \
    thdserialtask.h \
    threadcheckstate.h \
    threadcmd.h \
    threadcommcmd.h \
    threadreadinfo.h \
    threadserialworker.h \
    widget.h \
    wndprogress.h \
    xchart.h

FORMS += \
    dlgautoresult.ui \
    dlgclean.ui \
    dlgdebug.ui \
    dlgdeviceajust.ui \
    dlginfo.ui \
    dlglightswitch.ui \
    dlgmaintain.ui \
    dlgmaintaindevice.ui \
    dlgmaintainmirror.ui \
    dlgmdjcalc.ui \
    dlgmeasure.ui \
    dlgmeasure2.ui \
    dlgmeasureinfo.ui \
    dlgmeasurepreset.ui \
    dlgmeasuresetting.ui \
    dlgmeasurestart.ui \
    dlgmeasurex.ui \
    dlgmirrorsetting.ui \
    dlgnumpad.ui \
    dlgpanel.ui \
    dlgpanneldate.ui \
    dlgpasue.ui \
    dlgpositionsetting.ui \
    dlgresult.ui \
    dlgresults.ui \
    dlgsamplecell.ui \
    dlgselfcheck.ui \
    dlgsetup.ui \
    dlgshutdown.ui \
    dlgsysinfo.ui \
    dlgsyssetting.ui \
    dlgtemperaturesetting.ui \
    dlgtimesetting.ui \
    dlgupdate.ui \
    dlgwash.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    pic.qrc
#ifndef WIN32
unix:!macx: LIBS += -L$$PWD/../../lib/lib/ -lfftw3
unix:!macx: LIBS += -L$$PWD/../../lib/lib/ -lFuelPredict
unix:!macx: LIBS += -L$$PWD/../../lib/lib/ -lifg2specDLL
unix:!macx: LIBS += -L$$PWD/../../lib/lib/ -lparaTestDll
unix:!macx: LIBS += -L$$PWD/../../lib/lib/ -lSpecMatch

INCLUDEPATH += $$PWD/../../lib/inc
DEPENDPATH += $$PWD/../../lib/inc


#endif

