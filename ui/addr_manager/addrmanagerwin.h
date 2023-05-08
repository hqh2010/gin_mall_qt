#ifndef ADDRMANAGERWIN_H
#define ADDRMANAGERWIN_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QRadioButton>
#include <QTextEdit>
#include <QLineEdit>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>

namespace Ui {
class AddrManagerWin;
}

class AddrManagerWin : public QMainWindow
{
    Q_OBJECT

public:
    explicit AddrManagerWin(QWidget *parent = nullptr);
    ~AddrManagerWin();
    bool eventFilter(QObject *obj, QEvent *event);
private:
    void init_ui();
    void on_edit_switch_label_clicked();
private:
    Ui::AddrManagerWin *ui;

    QLabel *addr_edit_switch = nullptr;
};

#endif // ADDRMANAGERWIN_H
