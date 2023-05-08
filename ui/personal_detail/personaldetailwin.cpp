#include "personaldetailwin.h"
#include "ui_personaldetailwin.h"

#include <QHBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QDebug>
#include <QCloseEvent>

#include "model/data/data_def.h"
#include "utils/common/common.h"
#include "utils/http/http_client.h"

extern UserInfo current_user;

void PersonalDetailWin::init_ui()
{
    QGroupBox *box1 = new QGroupBox;
    box1->setTitle(tr("个人中心"));
    QVBoxLayout *box1layout = new QVBoxLayout;
    QLabel *order_label = new QLabel;
    order_label->setText(tr("我的订单"));
    box1layout->addWidget(order_label);
    QLabel *cart_label = new QLabel;
    cart_label->setText(tr("我的购物车"));
    box1layout->addWidget(cart_label);
    box1layout->setAlignment(this, Qt::AlignCenter);
    box1->setLayout(box1layout);

    QGroupBox *box2 = new QGroupBox;
    box2->setTitle(tr("账户管理"));
    QVBoxLayout *box2layout = new QVBoxLayout;
    QLabel *my_label = new QLabel;
    my_label->setText(tr("账户信息"));
    box2layout->addWidget(my_label);
    addr_label = new QLabel;
    addr_label->setText(tr("收货地址管理"));

    // 开启悬停事件
    addr_label->setAttribute(Qt::WA_Hover, true);
    // 安装事件过滤器
    addr_label->installEventFilter(this);

    box2layout->addWidget(addr_label);
    box2layout->setAlignment(this, Qt::AlignCenter);
    box2->setLayout(box2layout);

    QGroupBox *box3 = new QGroupBox;
    box3->setTitle(tr("关于"));
    QVBoxLayout *box3layout = new QVBoxLayout;
    QLabel *about_label = new QLabel;
    about_label->setText(tr("关于我们"));
    box3layout->addWidget(about_label);
    box3layout->setAlignment(this, Qt::AlignCenter);
    box3->setLayout(box3layout);

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget(box1);
    vlayout->addWidget(box2);
    vlayout->addWidget(box3);

    QWidget *widgetleft = new QWidget;
    widgetleft->setLayout(vlayout);
    QVBoxLayout *vlayout1 = new QVBoxLayout;

    QHBoxLayout *hlayout0 = new QHBoxLayout;
    QLabel *img = new QLabel;
    if (current_user.id != -1)
    {
        int pos = current_user.avatar.lastIndexOf('/');
        QString img_name = current_user.avatar.mid(pos + 1);
        qInfo() << "AccountManage img_name:" << img_name;
        QString header;
        QString port;
        int ret = utils::getLocalConfig("ServiceAddr", header);
        ret |= utils::getLocalConfig("HttpPort", port);
        if (ret != 0)
        {
            return;
        }
        QString urlstr = QString("%1/static/imgs/avatar/user%2/%3").arg(header + port).arg(current_user.id).arg(img_name);
        QPixmap pixmap;
        QByteArray img_bytes;
        ret = HTTPCLIENT->download_img(urlstr, img_bytes);
        qInfo() << "AccountManage urlstr:" << urlstr << ret;
        if (ret == 0)
        {
            pixmap.loadFromData(img_bytes);
            utils::createDir("/var/tmp/gin-mall-qt/.cache/");
            // 缓存到本地
            QFile file(QString("/var/tmp/gin-mall-qt/.cache/").append(img_name));
            if (file.open(QIODevice::Truncate | QIODevice::WriteOnly))
            {
                file.write(img_bytes);
                file.close();
            }
        }
        else
        {
            // 加载默认图片
            pixmap.load("/home/xxxxx/Desktop/gin-mall-qt/gin-mall-qt-client-1.0.0/avatar.JPG");
        }
        // QPixmap pixmap("http://10.20.6.68:3000/static/imgs/avatar/avatar.JPG");
        pixmap = pixmap.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        img->setPixmap(pixmap);
        // 设置图片宽度
        img->heightForWidth(100);
    }

    // QPixmap pixmap;
    // pixmap.load("/home/uthuqinghong/Desktop/gin-mall-qt/gin-mall-qt-client-1.0.0/avatar.JPG");
    // pixmap = pixmap.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    // img->setPixmap(pixmap);

    hlayout0->addWidget(img);
    QLabel *name_label = new QLabel;
    // name_label->setText(current_user.user_name);
    name_label->setText("uos");
    hlayout0->addWidget(name_label);

    QVBoxLayout *vlayout10 = new QVBoxLayout;
    QLabel *level_label = new QLabel;
    level_label->setText(tr("账户安全：普通"));
    QLabel *phone_label = new QLabel;
    phone_label->setText(tr("绑定手机：12345678910"));
    QLabel *mail_label = new QLabel;
    mail_label->setText(tr("绑定邮箱：123456＠qq.com"));
    vlayout10->addWidget(level_label);
    vlayout10->addWidget(phone_label);
    vlayout10->addWidget(mail_label);
    // widget3 为账户安全相关信息
    QWidget *widget3 = new QWidget;
    widget3->setLayout(vlayout10);
    widget3->setFixedHeight(100);
    hlayout0->addWidget(widget3);

    QWidget *widget4 = new QWidget;
    widget4->setLayout(hlayout0);

    QLabel *split_label = new QLabel;
    split_label->setFixedHeight(1);
    // 设置样式表
    split_label->setStyleSheet("QLabel{background-color:rgb(0,0,0);}");

    QVBoxLayout *vlayout0 = new QVBoxLayout;
    vlayout0->addWidget(widget4);

    vlayout0->addWidget(split_label);
    // vlayout0->setAlignment(this, Qt::AlignTop);

    // 待支付定单　
    QHBoxLayout *hlayout1 = new QHBoxLayout;
    QLabel *pay_img = new QLabel;
    QPixmap pay_map;
    pay_map.load(":/icon/to_pay.png");
    pay_map = pay_map.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    pay_img->setPixmap(pay_map);

    QVBoxLayout *vlayout11 = new QVBoxLayout;
    QLabel *to_pay_label = new QLabel;
    to_pay_label->setText(tr(QString("待支付定单：%1").arg(0).toLocal8Bit()));
    vlayout11->addWidget(to_pay_label);
    QLabel *view_pay_label = new QLabel;
    view_pay_label->setText(tr("查看待支付定单>"));
    view_pay_label->setStyleSheet("color:blue;");
    // setStyleSheet("color:#ff6600;");
    vlayout11->addWidget(view_pay_label);
    QWidget *widget5 = new QWidget;
    widget5->setLayout(vlayout11);
    widget5->setFixedHeight(100);

    hlayout1->addWidget(pay_img);
    hlayout1->addWidget(widget5);

    // QWidget *widget6 = new QWidget;
    // widget6->setLayout(hlayout1);

    // vlayout0->addWidget(widget6);

    // 待收货定单
    // QHBoxLayout *hlayout2 = new QHBoxLayout;
    QLabel *payed_img = new QLabel;
    QPixmap payed_map;
    payed_map.load(":/icon/payed_goods.png");
    payed_map = payed_map.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    payed_img->setPixmap(payed_map);

    QVBoxLayout *vlayout21 = new QVBoxLayout;
    QLabel *payed_label = new QLabel;
    payed_label->setText(tr(QString("待收货定单：%1").arg(0).toLocal8Bit()));
    vlayout21->addWidget(payed_label);
    QLabel *view_payed_label = new QLabel;
    view_payed_label->setText(tr("查看待收货定单>"));
    view_payed_label->setStyleSheet("color:blue;");
    // setStyleSheet("color:#ff6600;");
    vlayout21->addWidget(view_payed_label);
    QWidget *widget7 = new QWidget;
    widget7->setLayout(vlayout21);
    widget7->setFixedHeight(100);

    hlayout1->addWidget(payed_img);
    hlayout1->addWidget(widget7);

    QWidget *widget8 = new QWidget;
    // widget8->setLayout(hlayout2);
    widget8->setLayout(hlayout1);

    vlayout0->addWidget(widget8);

    vlayout0->setStretchFactor(widget4, 2);
    vlayout0->setStretchFactor(split_label, 1);
    vlayout0->setStretchFactor(widget8, 4);

    // vlayout0->addStretch();
    QWidget *widgetright = new QWidget;
    widgetright->setLayout(vlayout0);

    QHBoxLayout *hlayout = new QHBoxLayout;
    // 设置显示比例
    hlayout->addWidget(widgetleft);
    hlayout->setStretchFactor(widgetleft, 2);
    // hlayout->addStretch(1);
    hlayout->addWidget(widgetright);
    hlayout->setStretchFactor(widgetright, 4);

    ui->centralwidget->setLayout(hlayout);

    this->setWindowTitle(tr("个人中心"));
    // 窗体没有最大化最小化按钮
    this->setWindowFlag(Qt::Dialog);
    // 隐藏最大最小化
    // this->setWindowFlags(this->windowFlags()&~Qt::WindowMinMaxButtonsHint);
    // 窗口可以最小化，但不能最大化
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowMinMaxButtonsHint | Qt::WindowMinimizeButtonHint);
    // 窗口固定大小，禁止拖动右下角改变大小
    setFixedSize(800, 600);
}

PersonalDetailWin::PersonalDetailWin(QWidget *parent) : QMainWindow(parent),
                                                        ui(new Ui::PersonalDetailWin)
{
    ui->setupUi(this);
    init_ui();
}

void PersonalDetailWin::on_addr_label_clicked()
{
    this->hide();
    if (!addr_win)
    {
        addr_win = new AddrManagerWin;
    }
    addr_win->show();
}

void PersonalDetailWin::closeEvent(QCloseEvent *event)
{
    // 忽略要关闭这个窗口的事件，当前窗口就不会被关闭
    event->ignore();
    emit personalToHomeWin();
}

bool PersonalDetailWin::eventFilter(QObject *obj, QEvent *event)
{
    switch (event->type())
    {
    case QEvent::HoverEnter:
        if (obj == addr_label)
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
        if (obj == addr_label)
        {
            QPalette pa;
            pa.setColor(QPalette::WindowText, Qt::black);
            QLabel *label = (QLabel *)obj;
            label->setPalette(pa);
            QApplication::restoreOverrideCursor();
        }
        break;
    case QEvent::MouseButtonPress:
    {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        if (mouseEvent->button() == Qt::LeftButton)
        {
            if (obj == addr_label)
            {
                on_addr_label_clicked();
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

PersonalDetailWin::~PersonalDetailWin()
{
    delete ui;
}
