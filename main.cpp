#include <QApplication>
#include <qdesktopwidget.h>
#include <QTranslator>
#include <QLocale>
#include <QDebug>

#include "ui/carousel_img/carouselimagewidget.h"

#include "utils/common/common.h"
#include "ui/login/login.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // 设置运行时图标
    QApplication::setWindowIcon(QIcon(":/icon/cart.png"));
    QLocale local = QLocale::system();
    QLocale::Language lang = local.language();
    qInfo() << "lang=" << lang;

    QLocale::Country country = local.country();
    qInfo() << "country=" << country;

    QString name = local.name();
    qInfo() << "name=" << name;
    QString lan_res_path = QString(":/translations/i18n_%1.qm").arg(name);
    if (!utils::fileExists(lan_res_path))
    {
        qCritical() << "language cfg file " << lan_res_path << " not exist";
    }
    // 根据系统语言加载
    QTranslator translator;
    bool ret = translator.load(lan_res_path);
    a.installTranslator(&translator);
    Login w;
    QDesktopWidget *desktop = QApplication::desktop();
    w.move((desktop->width() - w.width()) / 2, (desktop->height() - w.height()) / 2);
    w.show();

    // CarouselImageWidget w;
    // w.addImage("/home/uthuqinghong/Desktop/gin-mall-qt/gin-mall-qt-client-1.0.0/carousel_img_res/1.jpg");
    // w.addImage("/home/uthuqinghong/Desktop/gin-mall-qt/gin-mall-qt-client-1.0.0/carousel_img_res/2.jpg");
    // w.addImage("/home/uthuqinghong/Desktop/gin-mall-qt/gin-mall-qt-client-1.0.0/carousel_img_res/3.jpg");
    // w.addImage("/home/uthuqinghong/Desktop/gin-mall-qt/gin-mall-qt-client-1.0.0/carousel_img_res/4.jpg");
    // w.addImage("/home/uthuqinghong/Desktop/gin-mall-qt/gin-mall-qt-client-1.0.0/carousel_img_res/5.jpg");
    // w.setControlButtonColor(Qt::yellow);
    // w.setBorderColor(Qt::red);
    // w.setImageChangeDuration(2000);
    // w.startPlay();

    // QDesktopWidget *desktop = QApplication::desktop();
    // w.move((desktop->width() - w.width()) / 2, (desktop->height() - w.height()) / 2);
    // qInfo() << "tttttttttttttttttttt height:" << w.height() << ", width:" << w.width();
    // w.show();

    return a.exec();
}
