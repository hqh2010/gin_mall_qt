#include "home.h"
#include "ui_home.h"
#include <QDebug>

#include "model/data/data_def.h"
#include "utils/common/common.h"
#include "utils/http/http_client.h"
#include <QHBoxLayout>

extern UserInfo current_user;

void Home::init_ui()
{
    ui->search_btn->setText(tr("搜索"));
    ui->search_edit->setPlaceholderText(tr("请输入搜索内容"));

    ui->favorite_label->setText(tr("我的收藏"));
    ui->order_label->setText(tr("我的订单"));
    // to do 购物车显示图片和数量
    ui->cart_label->setText(tr("购物车"));

    // 初始化首页轮播图
    ui->tabWidget->setCurrentIndex(0);
    ui->tabWidget->setTabText(0, tr("首页"));
    ui->tabWidget->setTabText(1, tr("全部商品"));
    ui->tabWidget->setTabText(2, tr("关于我们"));
    ui->tabWidget->setFixedSize(QSize(850, 750));
    this->setFixedSize(QSize(850, 900));

    ui->first_tab->setStyleSheet("background-color:white;");
    CarouselImageWidget* carousel_img = ui->first_tab->findChild<CarouselImageWidget*>("carousel_img_widget");
    carousel_img->addImage("/home/uthuqinghong/Desktop/gin-mall-qt/gin-mall-qt-client-1.0.0/carousel_img_res/1.jpg");
    carousel_img->addImage("/home/uthuqinghong/Desktop/gin-mall-qt/gin-mall-qt-client-1.0.0/carousel_img_res/2.jpg");
    carousel_img->addImage("/home/uthuqinghong/Desktop/gin-mall-qt/gin-mall-qt-client-1.0.0/carousel_img_res/3.jpg");
    carousel_img->addImage("/home/uthuqinghong/Desktop/gin-mall-qt/gin-mall-qt-client-1.0.0/carousel_img_res/4.jpg");
    carousel_img->addImage("/home/uthuqinghong/Desktop/gin-mall-qt/gin-mall-qt-client-1.0.0/carousel_img_res/5.jpg");
    carousel_img->setControlButtonColor(Qt::yellow);
    carousel_img->setBorderColor(Qt::red);
    carousel_img->setImageChangeDuration(2000);
    carousel_img->startPlay();
    qInfo() << "tttttttttttttttttttt height:" << carousel_img->height() << ", width:" << carousel_img->width();
    // QWidget *widget = new QWidget();
    // QLineEdit *lineEdit = new QLineEdit();
    // QPushButton *pushButton = new QPushButton("Test");
    // QVBoxLayout *vLayout = new QVBoxLayout();
    // vLayout->addWidget(lineEdit);
    // vLayout->addWidget(pushButton);
    // widget->setLayout(vLayout);
    // ui->tabWidget->addTab(widget, tr("首页"));


    this->setWindowTitle(tr("Shopping Mall"));
    // 窗体没有最大化最小化按钮
    this->setWindowFlag(Qt::Dialog);
    // 隐藏最大最小化
    // this->setWindowFlags(this->windowFlags()&~Qt::WindowMinMaxButtonsHint);
    // 窗口可以最小化，但不能最大化
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowMinMaxButtonsHint | Qt::WindowMinimizeButtonHint);
    // 窗口固定大小，禁止拖动右下角改变大小
    setFixedSize(this->width(), this->height());


    connect(ui->tabWidget,SIGNAL(currentChanged(int)),this,SLOT(on_tab_change(int)));
    // connect(ui->user_info_comboBox, SIGNAL(currentTextChanged(const QString &text)), this, SLOT(on_comboBox_currentIndexChanged(const QString &arg)));
}

Home::Home(QWidget *parent) : QMainWindow(parent),
                              ui(new Ui::Home)
{
    ui->setupUi(this);
    init_ui();
}

Home::~Home()
{
    delete ui;
}

void Home::on_tab_change(int index)
{
    qInfo() << "on_tab_change index:" << index;
    //ui->tabWidget->setCurrentIndex(index);
}

void Home::on_search_btn_clicked()
{
}

void Home::showEvent(QShowEvent *event)
{
    if (current_user.id != -1)
    {
        int pos = current_user.avatar.lastIndexOf('/');
        QString img_name = current_user.avatar.mid(pos + 1);
        qInfo() << "Home::showEvent img_name:" << img_name;
        QString header;
        QString port;
        int ret = utils::getLocalConfig("ServiceAddr", header);
        ret |= utils::getLocalConfig("HttpPort", port);
        if (ret != 0)
        {
            return;
        }
        QString urlstr = QString("%1/static/imgs/avatar/%3").arg(header + port).arg(img_name);
        qInfo() << "Home::showEvent urlstr:" << urlstr;
        QPixmap pixmap;
        QByteArray img_bytes;
        ret = HTTPCLIENT->download_img(urlstr, img_bytes);
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
            pixmap.load("home/xxxxx/Desktop/gin-mall-qt/gin-mall-qt-client-1.0.0/avatar.JPG");
        }

        pixmap.loadFromData(img_bytes);
        // QPixmap pixmap("http://10.20.6.68:3000/static/imgs/avatar/avatar.JPG");
        pixmap = pixmap.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->user_img_label->setPixmap(pixmap);
        // 设置图片宽度
        ui->user_img_label->heightForWidth(100);
        ui->user_img_label->show();
        ui->user_info_comboBox->clear();
        ui->user_info_comboBox->addItem(tr(current_user.nickname.toLocal8Bit()));
        ui->user_info_comboBox->addItem(tr("帐户管理"));
        ui->user_info_comboBox->setCurrentText(current_user.nickname);
    }
    QWidget::showEvent(event);
}

void Home::on_user_info_comboBox_currentTextChanged(const QString &arg1)
{
    qInfo() << "tttttttttttt comboBox text:" << arg1;
}
