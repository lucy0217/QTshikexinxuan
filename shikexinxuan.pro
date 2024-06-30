QT       += core gui sql
QT       += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addfriend.cpp \
    changeicon.cpp \
    changepassword.cpp \
    comment.cpp \
    customtablemodel.cpp \
    customtableview.cpp \
    friendinfo.cpp \
    friendlist.cpp \
    friendwidget.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    mydialog.cpp \
    searchfriend.cpp \
    setting.cpp \
    user.cpp \
    writecomment.cpp

HEADERS += \
    addfriend.h \
    changeicon.h \
    changepassword.h \
    comment.h \
    customtablemodel.h \
    customtableview.h \
    friendinfo.h \
    friendlist.h \
    friendwidget.h \
    login.h \
    mainwindow.h \
    mydialog.h \
    searchfriend.h \
    setting.h \
    user.h \
    writecomment.h

FORMS += \
    addfriend.ui \
    changeicon.ui \
    changepassword.ui \
    comment.ui \
    friendinfo.ui \
    friendlist.ui \
    friendwidget.ui \
    login.ui \
    mainwindow.ui \
    mydialog.ui \
    searchfriend.ui \
    setting.ui \
    writecomment.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    resources.qrc
