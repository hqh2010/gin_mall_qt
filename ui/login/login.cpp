#include "login.h"
#include "ui_login.h"

#include "utils/http/http_client.h"
#include "utils/serialize/serialize.h"

#include "model/data/data_def.h"

#include <qdesktopwidget.h>
#include <QDebug>
#include <QLineEdit>
#include <QMessageBox>
#include <QMouseEvent>

#include <QJsonDocument>
#include <QJsonObject>
#include <QTextCodec>

UserInfo current_user = {
    .id = -1, 
    .user_name = QString(),
    .pwd = QString(),
    .email = QString(),
    .nickname = QString(),
    .Status = QString(),
    .avatar = QString(),
    .money = QString(),
    .token = QString()
};

void Login::init_ui()
{
    // ui->login_name->setText(tr("用户名"));
    // ui->login_pwd->setText(tr("密码"));
    ui->login_name->setText(tr("login_name"));
    ui->login_pwd->setText(tr("login_pwd"));

    // ui->verify_label->setText(tr("看不清楚？换一张"));
    // ui->verify_edit->setPlaceholderText(tr("请输入验证码"));
    ui->verify_label->setText(tr("change_verify_code_label"));
    ui->verify_edit->setPlaceholderText(tr("verify_code_edit"));

    // ui->account_edit->setPlaceholderText(tr("请输入账号"));
    // ui->pwd_edit->setPlaceholderText(tr("请输入密码"));
    ui->account_edit->setPlaceholderText(tr("login_name_hint"));
    ui->pwd_edit->setPlaceholderText(tr("login_pwd_hint"));

    ui->pwd_edit->setEchoMode(QLineEdit::Password);

    // ui->login_btn->setText(tr("登录"));
    // ui->cancel_btn->setText(tr("取消"));
    ui->login_btn->setText(tr("login_btn_txt"));
    ui->cancel_btn->setText(tr("cancel_btn_txt"));

    // ui->find_pwd->setText(tr("忘记密码？"));
    // ui->reg_account->setText(tr("没有账号？去注册"));
    ui->find_pwd->setText(tr("find_pwd_label_txt"));
    ui->reg_account->setText(tr("to_register_label_txt"));

    // 开启悬停事件
    ui->find_pwd->setAttribute(Qt::WA_Hover, true);
    // 安装事件过滤器
    ui->find_pwd->installEventFilter(this);

    // 开启悬停事件
    ui->reg_account->setAttribute(Qt::WA_Hover, true);
    // 安装事件过滤器
    ui->reg_account->installEventFilter(this);

    // 开启悬停事件
    ui->verify_label->setAttribute(Qt::WA_Hover, true);
    // 安装事件过滤器
    ui->verify_label->installEventFilter(this);

    // 验证码
    ui->widget_verification->setBackgroundStyle(BackgroundStyle::E_DOT);
    qInfo() << "tttttttttttttttttttt init_ui verify code:" << ui->widget_verification->getVerificationCode().toUpper();

    // this->setWindowTitle(tr("登录"));
    this->setWindowTitle(tr("login_win_title"));
    // 窗体没有最大化最小化按钮
    this->setWindowFlag(Qt::Dialog);
    // 隐藏最大最小化
    // this->setWindowFlags(this->windowFlags()&~Qt::WindowMinMaxButtonsHint);
    // 窗口可以最小化，但不能最大化
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowMinMaxButtonsHint | Qt::WindowMinimizeButtonHint);
    // 窗口固定大小，禁止拖动右下角改变大小
    setFixedSize(this->width(), this->height());

    connect(ui->login_btn, SIGNAL(clicked()), this, SLOT(on_login_btn_clicked));
    connect(ui->cancel_btn, SIGNAL(clicked()), qApp, SLOT(quit()));

    QObject::connect(&reg_win, SIGNAL(regToLoginWin()), this, SLOT(on_reg_2_login()));
    QObject::connect(&pwd_win, SIGNAL(pwdToLoginWin()), this, SLOT(on_pwd_2_login()));
}

Login::Login(QWidget *parent) : QMainWindow(parent),
                                ui(new Ui::Login)
{
    ui->setupUi(this);
    init_ui();
}

Login::~Login()
{
    delete ui;
}

void Login::showEvent(QShowEvent *event)
{
    // 设置默认焦点
    // https://blog.csdn.net/hp_cpp/article/details/105847810
    // https://zhuanlan.zhihu.com/p/580701824
    ui->account_edit->setFocus();
    QWidget::showEvent(event);
}

bool Login::verifyCode()
{
    auto codes = ui->widget_verification->getVerificationCode().toUpper();
    auto lineEditText = ui->verify_edit->text().trimmed().toUpper();
    if (codes == lineEditText)
    {
        return true;
    }
    return false;
}

void Login::on_login_btn_clicked()
{
    if (!verifyCode())
    {
        QMessageBox msgBox;
        // msgBox.setWindowTitle(tr("警告"));
        msgBox.setWindowTitle(tr("login_box_title"));
        // msgBox.setText(tr("验证码输入有误"));
        msgBox.setText(tr("login_box_verify_msg"));
        msgBox.setStandardButtons(QMessageBox::Ok);
        // msgBox.setButtonText(QMessageBox::Ok, tr("确定"));
        msgBox.setButtonText(QMessageBox::Ok, tr("login_box_btn"));

        msgBox.setIcon(QMessageBox::Warning);
        msgBox.exec();
        return;
    }

    if (ui->account_edit->text().trimmed().isEmpty())
    {
        QMessageBox msgBox;
        // msgBox.setWindowTitle(tr("警告"));
        msgBox.setWindowTitle(tr("login_box_title"));
        // msgBox.setText(tr("用户名不能为空"));
        msgBox.setText(tr("login_box_name_empty"));
        msgBox.setStandardButtons(QMessageBox::Ok);
        // msgBox.setButtonText(QMessageBox::Ok, tr("确定"));
        msgBox.setButtonText(QMessageBox::Ok, tr("login_box_btn"));
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.exec();
        return;
    }
    if (ui->pwd_edit->text().trimmed().isEmpty())
    {
        QMessageBox msgBox;
        // msgBox.setWindowTitle(tr("警告"));
        msgBox.setWindowTitle(tr("login_box_title"));
        // msgBox.setText(tr("密码不能为空"));
        msgBox.setText(tr("login_box_pwd_empty"));
        msgBox.setStandardButtons(QMessageBox::Ok);
        // msgBox.setButtonText(QMessageBox::Ok, tr("确定"));
        msgBox.setButtonText(QMessageBox::Ok, tr("login_box_btn"));
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.exec();
        return;
    }
    QString login_name = ui->account_edit->text().trimmed();
    QString pwd = ui->pwd_edit->text().trimmed();
    qInfo() << "login name:" + login_name << ", pwd:" + pwd;

    QString out = "";
    QString err_info = "";
    QMap<QString, QString> mapData;
    mapData.insert(MALL_KEY_USER_NAME, login_name);
    mapData.insert(MALL_KEY_PWD, pwd);
    int ret = HTTPCLIENT->post(LOGIN, mapData, "", out, err_info);
    ret |= utils::load_from_json(out, current_user, err_info);
    qInfo() << "load_from_json ret:" << ret << current_user.nickname << ", token:" << current_user.token;
    if (ret)
    {
        // to do根据服务端状态码来显示错误信息并全球化
        QMessageBox msgBox;
        // msgBox.setWindowTitle(tr("警告"));
        msgBox.setWindowTitle(tr("login_box_title"));
        msgBox.setText(tr(err_info.toLocal8Bit()));
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setButtonText(QMessageBox::Ok, tr("login_box_btn"));
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.exec();
        return;
    }
    qInfo().noquote() << out;
    // 跳转主页面
    QDesktopWidget *desktop = QApplication::desktop();
    home_win.move((desktop->width() - home_win.width()) / 2, (desktop->height() - home_win.height()) / 2);
    home_win.show();
    this->hide();
}

bool Login::eventFilter(QObject *obj, QEvent *event)
{
    switch (event->type())
    {
    case QEvent::HoverEnter:
        if (obj == ui->find_pwd || obj == ui->reg_account || obj == ui->verify_label)
        {
            QPalette pa;
            pa.setColor(QPalette::WindowText, Qt::blue);
            QLabel *label = (QLabel *)obj;
            label->setPalette(pa);
            // 设置鼠标样式
            QCursor waitCursor = Qt::PointingHandCursor;
            QApplication::setOverrideCursor(waitCursor);
        }
        break;
    case QEvent::HoverLeave:
        if (obj == ui->find_pwd || obj == ui->reg_account || obj == ui->verify_label)
        {
            QPalette pa;
            pa.setColor(QPalette::WindowText, Qt::black);
            QLabel *label = (QLabel *)obj;
            label->setPalette(pa);
            QApplication::restoreOverrideCursor();
        }
        break;
    // https://blog.csdn.net/Vichael_Chan/article/details/100143032
    case QEvent::MouseButtonPress:
    {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        if (mouseEvent->button() == Qt::LeftButton)
        {
            if (obj == ui->find_pwd)
            {
                on_find_pwd_clicked();
            }
            if (obj == ui->reg_account)
            {
                on_reg_account_clicked();
            }
            if (obj == ui->verify_label)
            {
                on_verify_label_clicked();
            }
            return true;
        }
        break;
    }
    default:
        break;
    }
    return QWidget::eventFilter(obj, event);
}

void Login::on_reg_account_clicked()
{
    qInfo() << "on_reg_account_clicked";
    // Register *w = new Register(this);
    // 窗口跳转 https://blog.csdn.net/zxy131072/article/details/95475136
    QDesktopWidget *desktop = QApplication::desktop();
    reg_win.move((desktop->width() - reg_win.width()) / 2, (desktop->height() - reg_win.height()) / 2);
    reg_win.is_from_reg = true;
    reg_win.show();
    this->hide();
}

void Login::on_find_pwd_clicked()
{
    qInfo() << "on_find_pwd_clicked";
    QDesktopWidget *desktop = QApplication::desktop();
    pwd_win.move((desktop->width() - pwd_win.width()) / 2, (desktop->height() - pwd_win.height()) / 2);
    pwd_win.show();
    this->hide();
}

void Login::on_verify_label_clicked()
{
    qInfo() << "on_verify_label_clicked";
    ui->widget_verification->updateCode();
}

void Login::on_reg_2_login()
{
    qInfo() << "on_reg_account_clicked";
    // Register *w = new Register(this);
    // 窗口跳转 https://blog.csdn.net/zxy131072/article/details/95475136
    // QDesktopWidget *desktop = QApplication::desktop();
    // reg_win.move((desktop->width() - reg_win.width()) / 2, (desktop->height() - reg_win.height()) / 2);
    reg_win.hide();
    this->show();
}

void Login::on_pwd_2_login()
{
    qInfo() << "on_reg_account_clicked";
    // Register *w = new Register(this);
    // 窗口跳转 https://blog.csdn.net/zxy131072/article/details/95475136
    // QDesktopWidget *desktop = QApplication::desktop();
    // reg_win.move((desktop->width() - reg_win.width()) / 2, (desktop->height() - reg_win.height()) / 2);
    pwd_win.hide();
    this->show();
}

void Login::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type())
    {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
