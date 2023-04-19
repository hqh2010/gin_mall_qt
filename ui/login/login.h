#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include "ui/register/register.h"
#include "ui/find_pwd/findpwd.h"
#include "ui/home/home.h"
namespace Ui
{
    class Login;
}

class Login : public QMainWindow
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

    bool eventFilter(QObject *obj, QEvent *event) override;
    void showEvent(QShowEvent *event) override;
    void changeEvent(QEvent *e) override;
private slots:
    void on_login_btn_clicked();

    // 注册窗口返回登陆窗口
    void on_reg_2_login();

    void on_pwd_2_login();

private:
    void init_ui();

    void on_find_pwd_clicked();

    void on_reg_account_clicked();

    void on_verify_label_clicked();

    bool verifyCode();

private:
    Ui::Login *ui;

    Register reg_win;

    FindPwd pwd_win;

    Home home_win;
};

#endif // LOGIN_H
