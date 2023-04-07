#include <QApplication>
#include <qdesktopwidget.h>

#include "ui/login/login.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login w;
    QDesktopWidget *desktop = QApplication::desktop();
    w.move((desktop->width() - w.width()) / 2, (desktop->height() - w.height()) / 2);
    w.show();

    return a.exec();
}
