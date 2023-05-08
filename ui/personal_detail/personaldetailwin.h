#ifndef PERSONALDETAILWIN_H
#define PERSONALDETAILWIN_H

#include <QMainWindow>
#include <QLabel>
#include <QDebug>
#include <QCloseEvent>
#include "ui/addr_manager/addrmanagerwin.h"
namespace Ui
{
    class PersonalDetailWin;
}

class PersonalDetailWin : public QMainWindow
{
    Q_OBJECT

public:
    explicit PersonalDetailWin(QWidget *parent = nullptr);
    ~PersonalDetailWin();

    void closeEvent(QCloseEvent *event);
    bool eventFilter(QObject *obj, QEvent *event);
signals:
    void personalToHomeWin();

private:
    void init_ui();
    void on_addr_label_clicked();

private:
    Ui::PersonalDetailWin *ui;
    QLabel *addr_label = nullptr;
    AddrManagerWin* addr_win = nullptr;
};

#endif // PERSONALDETAILWIN_H
