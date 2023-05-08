#-------------------------------------------------
#
# Project created by QtCreator 2023-03-21T15:08:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets network

# 打印QT 版本
message(Qt Version = $$[QT_VERSION])
message(arch = $$QT_ARCH)

VERSION = 1.0.0.1
TARGET = gin_mall_qt_client
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

INCLUDEPATH += $$PWD/ui/verification $$PWD/ui/carousel_img $$PWD/ui/about

TRANSLATIONS = translations/i18n_zh_CN.ts translations/i18n_en_US.ts

ICON = icon/cart.png

SOURCES += \
        main.cpp \
    ui/login/login.cpp \
    ui/register/register.cpp \
    ui/find_pwd/findpwd.cpp \
    utils/http/http_client.cpp \
    utils/serialize/serialize.cpp \
    utils/common/common.cpp \
    ui/verification/verification.cpp \
    ui/home/home.cpp \
    ui/carousel_img/carouselimagewidget.cpp \
    ui/test/test.cpp \
    ui/home/custom_list_item/custilistitem.cpp \
    ui/account_manage/accountmanage.cpp \
    ui/about/aboutappwidget.cpp \
    ui/product_detail/productdetail.cpp \
    ui/cart/cartwin.cpp \
    ui/cart/checkboxheaderview.cpp \
    ui/personal_detail/personaldetailwin.cpp \
    ui/addr_manager/addrmanagerwin.cpp
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
    ui/verification/verification.h \
    ui/home/home.h \
    ui/carousel_img/carouselimagewidget.h \
    ui/test/test.h \
    ui/home/custom_list_item/custilistitem.h \
    ui/account_manage/accountmanage.h \
    ui/about/aboutappwidget.h \
    ui/product_detail/productdetail.h \
    ui/cart/cartwin.h \
    ui/cart/checkboxheaderview.h \
    ui/personal_detail/personaldetailwin.h \
    ui/addr_manager/addrmanagerwin.h
FORMS += \
    ui/login/login.ui \
    ui/register/register.ui \
    ui/find_pwd/findpwd.ui \
    ui/verification/verification.ui \
    ui/home/home.ui \
    ui/carousel_img/carouselimagewidget.ui \
    ui/test/test.ui \
    ui/account_manage/accountmanage.ui \
    ui/about/aboutappwidget.ui \
    ui/product_detail/productdetail.ui \
    ui/cart/cartwin.ui \
    ui/personal_detail/personaldetailwin.ui \
    ui/addr_manager/addrmanagerwin.ui

RESOURCES += \
    res.qrc

# DEFINES += INSTALL_PATH_DEAULT
INSTALL_PATH_DEAULT = /usr/bin

#contains(DEFINES, INSTALL_PATH){
#    message(Prefix=$$INSTALL_PATH)
#}else{
#    DEFINES += INSTALL_PATH
#    INSTALL_PATH = $$INSTALL_PATH_DEAULT
#    message(default=$$INSTALL_PATH)
#}

# Default rules for deployment.
# qnx: target.path = $$[PWD]
# else: unix:!android: target.path = /home/xxxxxx/Desktop/gin-mall-qt/gin_mall_qt/build/bin

message(current path = $$PWD)
target.files=$$PWD/gin_mall_qt_client
target.path=$$INSTALL_PATH_DEAULT
!isEmpty(target.path): INSTALLS += target

# 安装图标文件
icon_cfg.files=$$PWD/icon/cart.png
icon_cfg.path=/etc/gin-mall-qt-client/icon/
unix:icon_cfg.extra = mkdir -p /etc/gin-mall-qt-client/icon
# 安装服务端配置文件
server_cfg.files=$$PWD/misc/conf/config
server_cfg.path=/etc/gin-mall-qt-client
# 安装desktop文件
desktop_cfg.files=$$PWD/misc/desktop/org.gin-mall-qt-client.desktop
desktop_cfg.path=/usr/share/applications/

INSTALLS += icon_cfg server_cfg desktop_cfg
