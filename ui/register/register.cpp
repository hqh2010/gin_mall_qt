#include "register.h"
#include "ui_register.h"

#include <QDebug>
#include <QCloseEvent>

Register::Register(QWidget *parent) : QMainWindow(parent),
                                      ui(new Ui::Register)
{
    ui->setupUi(this);
    init_ui();
}

void Register::init_ui()
{
    // ui->login_name->setText(tr("user name"));
    ui->user_name_label->setText("用户名");
    ui->user_name_edit->setPlaceholderText("请输入用户名");

    ui->nick_name_label->setText("昵称");
    ui->nick_name_edit->setPlaceholderText("请输入昵称");

    ui->pwd_label->setText("密码");
    ui->pwd_edit->setPlaceholderText("请输入密码");
    ui->pwd_edit->setEchoMode(QLineEdit::Password);

    ui->pwd_confirm_label->setText("确认密码");
    ui->pwd_confirm_edit->setPlaceholderText("请再次输入密码");
    ui->pwd_confirm_edit->setEchoMode(QLineEdit::Password);

    ui->mail_label->setText("邮箱");
    ui->mail_edit->setPlaceholderText("请输入邮箱");

    ui->reg_btn->setText("注册");
    this->setWindowTitle("注册");
    // 窗体没有最大化最小化按钮
    this->setWindowFlag(Qt::Dialog);
    // 隐藏最大最小化
    // this->setWindowFlags(this->windowFlags()&~Qt::WindowMinMaxButtonsHint);
    // 窗口可以最小化，但不能最大化
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowMinMaxButtonsHint | Qt::WindowMinimizeButtonHint);
    // 窗口固定大小，禁止拖动右下角改变大小
    setFixedSize(this->width(), this->height());

    connect(ui->reg_btn, SIGNAL(clicked()), this, SLOT(on_reg_btn_clicked));
}

void Register::showEvent(QShowEvent *event)
{
    qInfo() << "Register ttttttttttttt showEvent";
    // 设置默认焦点
    // https://blog.csdn.net/hp_cpp/article/details/105847810
    // https://zhuanlan.zhihu.com/p/580701824
    ui->user_name_edit->setFocus();
    // 如果从登陆页面跳转，则清除注册信息
    if (is_from_reg)
    {
        ui->user_name_edit->clear();
        is_from_reg = false;
    }
    QWidget::showEvent(event);
}

void Register::on_reg_btn_clicked()
{
    qInfo() << ui->user_name_edit->text().trimmed() << "register success";
    emit regToLoginWin();
}

void Register::closeEvent(QCloseEvent *event)
{
    // 忽略要关闭这个窗口的事件，当前窗口就不会被关闭
    event->ignore();
    emit regToLoginWin();
}

Register::~Register()
{
    delete ui;
}
