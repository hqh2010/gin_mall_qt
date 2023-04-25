#ifndef ACCOUNTMANAGE_H
#define ACCOUNTMANAGE_H

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include "utils/http/http_client.h"

namespace Ui {
class AccountManage;
}

class AccountManage : public QMainWindow
{
    Q_OBJECT

public:
    explicit AccountManage(QWidget *parent = nullptr);
    ~AccountManage();

    void closeEvent(QCloseEvent *event);
    bool eventFilter(QObject *obj, QEvent *event) override;
private slots:
    void onImgButtonClicked();

signals:
    void accountToHomeWin();

private:
    Ui::AccountManage *ui;

    QLabel *img;
};

#endif // ACCOUNTMANAGE_H
