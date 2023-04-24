#include "register.h"
#include "ui_register.h"

#include <QCloseEvent>
#include <QDebug>
#include <QMessageBox>

#include "model/data/data_def.h"

#include "utils/http/http_client.h"
#include "utils/serialize/serialize.h"

Register::Register(QWidget *parent) : QMainWindow(parent),
                                      ui(new Ui::Register)
{
    ui->setupUi(this);
    init_ui();
}

void Register::init_ui()
{
    // ui->user_name_label->setText(tr("用户名"));
    // ui->user_name_edit->setPlaceholderText(tr("请输入用户名"));
    ui->user_name_label->setText(tr("user_login_name"));
    ui->user_name_edit->setPlaceholderText(tr("login_name_hint"));

    // ui->nick_name_label->setText(tr("昵称"));
    // ui->nick_name_edit->setPlaceholderText(tr("请输入昵称"));
    ui->nick_name_label->setText(tr("user_nick_name"));
    ui->nick_name_edit->setPlaceholderText(tr("user_nick_name_hint"));

    // ui->pwd_label->setText(tr("密码"));
    // ui->pwd_edit->setPlaceholderText(tr("请输入密码"));
    ui->pwd_label->setText(tr("user_login_pwd"));
    ui->pwd_edit->setPlaceholderText(tr("login_pwd_hint"));

    ui->pwd_edit->setEchoMode(QLineEdit::Password);

    // ui->pwd_confirm_label->setText(tr("确认密码"));
    // ui->pwd_confirm_edit->setPlaceholderText(tr("请再次输入密码"));
    ui->pwd_confirm_label->setText(tr("confirm_label"));
    ui->pwd_confirm_edit->setPlaceholderText(tr("confirm_label_hint"));

    ui->pwd_confirm_edit->setEchoMode(QLineEdit::Password);

    // ui->mail_label->setText(tr("邮箱"));
    // ui->mail_edit->setPlaceholderText(tr("请输入邮箱"));
    ui->mail_label->setText(tr("mail_label"));
    ui->mail_edit->setPlaceholderText(tr("mail_label_hint"));

    // ui->reg_btn->setText(tr("注册"));
    ui->reg_btn->setText(tr("reg_btn_txt"));

    // this->setWindowTitle(tr("注册"));
    this->setWindowTitle(tr("reg_win_title"));
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
    if (ui->user_name_label->text().trimmed().isEmpty())
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle(tr("警告"));
        // msgBox.setWindowTitle(tr("reg_box_title"));
        msgBox.setText(tr("用户名不能为空"));
        // msgBox.setText(tr("reg_box_name_empty"));
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setButtonText(QMessageBox::Ok, tr("确定"));
        // msgBox.setButtonText(QMessageBox::Ok, tr("login_box_btn"));
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.exec();
        return;
    }
    // 校验用户名
    // 校验密码
    // 校验安全邮箱

    QString user_name = ui->user_name_edit->text().trimmed();
    QString nick_name = ui->nick_name_edit->text().trimmed();
    QString pwd = ui->pwd_edit->text().trimmed();
    QString mail = ui->mail_edit->text().trimmed();

    qInfo() << user_name << nick_name << pwd << mail;
    QString out = "";
    QString err_info = "";
    QMap<QString, QString> mapData;
    mapData.insert(MALL_KEY_USER_NAME, user_name);
    mapData.insert(MALL_KEY_PWD, pwd);
    mapData.insert(MALL_KEY_NICK_NAME, nick_name);
    mapData.insert(MALL_KEY_KEY, mail);

    int ret = HTTPCLIENT->post(REGISTER, mapData, out, err_info);
    // ret |= utils::load_from_json(out, current_user, err_info);
    // qInfo() << "load_from_json ret:" << ret << current_user.nickname << ", token:" << current_user.token;
    qInfo() << "load_from_json ret:" << ret << out;
    if (ret)
    {
        // to do根据服务端状态码来显示错误信息并全球化
        QMessageBox msgBox;
        msgBox.setWindowTitle(tr("警告"));
        // msgBox.setWindowTitle(tr("login_box_title"));
        msgBox.setText(tr(err_info.toLocal8Bit()));
        msgBox.setStandardButtons(QMessageBox::Ok);
        // msgBox.setButtonText(QMessageBox::Ok, tr("login_box_btn"));
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.exec();
        return;
    }

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
