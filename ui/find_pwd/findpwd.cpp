#include "findpwd.h"
#include "ui_findpwd.h"

#include <QCloseEvent>
#include <QDebug>
#include <QMessageBox>

void FindPwd::init_ui()
{
    // ui->login_name->setText(tr("user name"));
    // ui->mail_label->setText(tr("安全邮箱"));
    // ui->mail_edit->setPlaceholderText(tr("请输入邮箱账号"));
    ui->mail_label->setText(tr("mail_label"));
    ui->mail_edit->setPlaceholderText(tr("mail_label_hint"));

    // ui->pwd_label->setText(tr("密码"));
    // ui->pwd_edit->setPlaceholderText(tr("请输入密码"));
    ui->pwd_label->setText(tr("pwd_label"));
    ui->pwd_edit->setPlaceholderText(tr("pwd_hint"));

    ui->pwd_edit->setEchoMode(QLineEdit::Password);

    // ui->pwd_confirm_label->setText(tr("确认密码"));
    // ui->pwd_confirm_edit->setPlaceholderText(tr("请再次输入密码"));
    ui->pwd_confirm_label->setText(tr("confirm_pwd_label"));
    ui->pwd_confirm_edit->setPlaceholderText(tr("confirm_pwd_hint"));

    ui->pwd_confirm_edit->setEchoMode(QLineEdit::Password);

    // ui->reset_btn->setText(tr("重置"));
    ui->reset_btn->setText(tr("reset_btn_txt"));

    // this->setWindowTitle(tr("密码重置"));
    this->setWindowTitle(tr("findpwd_win_title"));
    // 窗体没有最大化最小化按钮
    this->setWindowFlag(Qt::Dialog);
    // 隐藏最大最小化
    // this->setWindowFlags(this->windowFlags()&~Qt::WindowMinMaxButtonsHint);
    // 窗口可以最小化，但不能最大化
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowMinMaxButtonsHint | Qt::WindowMinimizeButtonHint);
    // 窗口固定大小，禁止拖动右下角改变大小
    setFixedSize(this->width(), this->height());

    connect(ui->reset_btn, SIGNAL(clicked()), this, SLOT(on_reset_btn_clicked));
}

void FindPwd::on_reset_btn_clicked()
{
    qInfo() << "on_reset_btn_clicked()";
    // 向服务端发送重置请求
    // 成功则跳转登陆界面
    QMessageBox msgBox;
    // msgBox.setWindowTitle(tr("提示"));
    msgBox.setWindowTitle(tr("reset_result_title"));

    // msgBox.setText(tr("密码重置成功"));
    msgBox.setText(tr("reset_result_hint"));

    msgBox.setStandardButtons(QMessageBox::Ok);
    // msgBox.setButtonText(QMessageBox::Ok, tr("确定"));
    msgBox.setButtonText(QMessageBox::Ok, tr("reset_result_btn"));
    msgBox.setIcon(QMessageBox::Information);
    int ret = msgBox.exec();
    switch (ret)
    {
    case QMessageBox::Ok:
        emit pwdToLoginWin();
        break;
    case QMessageBox::Cancel:
        // Cancel was clicked
        break;
    default:
        // should never be reached
        break;
    }
}

void FindPwd::closeEvent(QCloseEvent *event)
{
    // 忽略要关闭这个窗口的事件，当前窗口就不会被关闭
    event->ignore();
    emit pwdToLoginWin();
}

FindPwd::FindPwd(QWidget *parent) : QMainWindow(parent),
                                    ui(new Ui::FindPwd)
{
    ui->setupUi(this);
    init_ui();
}

FindPwd::~FindPwd()
{
    delete ui;
}
