#-------------------------------------------------
#
# Project created by QtCreator 2023-03-21T15:08:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets network

TARGET = gin_mall_qt
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

INCLUDEPATH += $$PWD/ui/verification

TRANSLATIONS = translations/i18n_zh_CN.ts translations/i18n_en_US.ts

SOURCES += \
        main.cpp \
    ui/login/login.cpp \
    ui/register/register.cpp \
    ui/find_pwd/findpwd.cpp \
    utils/http/http_client.cpp \
    utils/serialize/serialize.cpp \
    utils/common/common.cpp \
    ui/verification/verification.cpp
HEADERS += \
    ui/login/login.h \
    ui/register/register.h \
    ui/find_pwd/findpwd.h \
    ui/find_pwd/findpwd.h \
    utils/singleton/singleton.h \
    utils/http/http_client.h \
    utils/common/common.h \
    utils/serialize/serialize.h \
    model/data/data_def.h \
    ui/verification/verification.h
FORMS += \
    ui/login/login.ui \
    ui/register/register.ui \
    ui/find_pwd/findpwd.ui \
    ui/verification/verification.ui

TARGET = gin_mall_qt
# Default rules for deployment.
qnx: target.path = /home/uthuqinghong/Desktop/gin-mall-qt/gin_mall_qt/build/bin
else: unix:!android: target.path = /home/uthuqinghong/Desktop/gin-mall-qt/gin_mall_qt/build/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    lan.qrc
