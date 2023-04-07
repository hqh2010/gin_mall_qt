#include "findpwd.h"
#include "ui_findpwd.h"

#include <QCloseEvent>
#include <QDebug>
#include <QMessageBox>

void FindPwd::init_ui()
{
    // ui->login_name->setText(tr("user name"));
    ui->mail_label->setText("安全邮箱");
    ui->mail_edit->setPlaceholderText("请输入邮箱账号");

    ui->pwd_label->setText("密码");
    ui->pwd_edit->setPlaceholderText("请输入密码");
    ui->pwd_edit->setEchoMode(QLineEdit::Password);

    ui->pwd_confirm_label->setText("确认密码");
    ui->pwd_confirm_edit->setPlaceholderText("请再次输入密码");
    ui->pwd_confirm_edit->setEchoMode(QLineEdit::Password);

    ui->mail_label->setText("邮箱");
    ui->mail_edit->setPlaceholderText("请输入邮箱");

    ui->reset_btn->setText("重置");

    this->setWindowTitle("密码重置");
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
    msgBox.setWindowTitle("提示");
    msgBox.setText(tr("密码重置成功"));
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setButtonText(QMessageBox::Ok, "确定");
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
