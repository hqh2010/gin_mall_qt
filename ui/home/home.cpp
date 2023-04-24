#include "home.h"
#include "ui_home.h"
#include <QDebug>

#include "model/data/data_def.h"
#include "utils/common/common.h"
#include "utils/http/http_client.h"
#include <QHBoxLayout>
#include <QScrollArea>

#include "carouselimagewidget.h"
#include "custom_list_item/custilistitem.h"

extern UserInfo current_user;

void Home::init_product_info(QListWidget *listWidget)
{
    // i代表行数
    for (int i = 0; i < 2; i++)
    {
        QWidget *widget2 = new QWidget(listWidget);

        QHBoxLayout *hLayout = new QHBoxLayout;
        // j 代表列数，每列4个
        for (int j = 0; j < 4; j++)
        {
            // QWidget *widget = new QWidget;
            // widget->setObjectName(QString("item%1").arg(4 * i + j + 1));
            // QVBoxLayout *verLayout = new QVBoxLayout;
            // verLayout->setContentsMargins(0, 0, 0, 0);
            // verLayout->setSpacing(10);
            // QLabel *icon_label = new QLabel;
            // QPixmap pixmap(QString("/home/uthuqinghong/Desktop/gin-mall-qt/gin-mall-qt-client-1.0.0/cup_res/cup%1.jpg").arg(4 * i + j + 1));
            // pixmap = pixmap.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            // icon_label->setPixmap(pixmap);
            // 点击事件交由父控件处理
            // icon_label->setAttribute(Qt::WA_TransparentForMouseEvents);
            // verLayout->addWidget(icon_label);
            // QLabel *dsc_label = new QLabel;
            // dsc_label->setText(tr(QString("cup%1").arg(4 * i + j + 1).toLocal8Bit()));
            // 点击事件交由父控件处理
            // dsc_label->setAttribute(Qt::WA_TransparentForMouseEvents);
            // verLayout->addWidget(dsc_label);
            // widget->setLayout(verLayout);
            // widget->show();
            // hLayout->addStretch();
            // hLayout->addWidget(widget);
            // connect(widget,SIGNAL(currentChanged(int)),this,SLOT(on_tab_change(int)));

            CustIListItem *widget = new CustIListItem(widget2);
            widget->set_item(4 * i + j + 1, tr(QString("cup%1").arg(4 * i + j + 1).toLocal8Bit()), QString("/home/uthuqinghong/Desktop/gin-mall-qt/gin-mall-qt-client-1.0.0/cup_res/cup%1.jpg").arg(4 * i + j + 1));
            // widget->show();
            hLayout->addStretch();
            hLayout->addWidget(widget);
        }
        hLayout->addStretch();
        // hLayout->setMargin(0);
        // hLayout->setSpacing(10);

        // QWidget *widget2 = new QWidget(this);
        widget2->setLayout(hLayout);
        widget2->show();
        QListWidgetItem *item = new QListWidgetItem();
        // 设置item的大小，大小应该比每个item
        item->setSizeHint(QSize(this->width(), 150));
        // 取消选中，否则点击时会选中整行
        item->setFlags(item->flags() & ~Qt::ItemIsSelectable);
        listWidget->addItem(item);
        listWidget->setItemWidget(item, widget2);
    }
}

void Home::set_listwidget(const int current_page)
{
    // 假设有 13 件商品
    int total_num = 13;
    // 每页显示　8　个 ，页码下标从1开始
    int start_num = 8 * (current_page - 1);
    int line_num = 1;
    if (total_num > start_num + 4)
    {
        line_num = 2;
    }
    int row_start = 2 * (current_page - 1);

    for (int i = row_start; i < row_start + line_num; i++)
    {
        QWidget *widget2 = new QWidget(product_listWidget);

        QHBoxLayout *hLayout = new QHBoxLayout;
        bool flag = true;
        // j 代表列数，每列4个
        for (int j = 0; j < 4; j++)
        {
            // QWidget *widget = new QWidget;
            // widget->setObjectName(QString("item%1").arg(4 * i + j + 1));
            // QVBoxLayout *verLayout = new QVBoxLayout;
            // verLayout->setContentsMargins(0, 0, 0, 0);
            // verLayout->setSpacing(10);
            // QLabel *icon_label = new QLabel;
            // QPixmap pixmap(QString("/home/uthuqinghong/Desktop/gin-mall-qt/gin-mall-qt-client-1.0.0/cup_res/cup%1.jpg").arg(4 * i + j + 1));
            // pixmap = pixmap.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            // icon_label->setPixmap(pixmap);
            // 点击事件交由父控件处理
            // icon_label->setAttribute(Qt::WA_TransparentForMouseEvents);
            // verLayout->addWidget(icon_label);
            // QLabel *dsc_label = new QLabel;
            // dsc_label->setText(tr(QString("cup%1").arg(4 * i + j + 1).toLocal8Bit()));
            // 点击事件交由父控件处理
            // dsc_label->setAttribute(Qt::WA_TransparentForMouseEvents);
            // verLayout->addWidget(dsc_label);
            // widget->setLayout(verLayout);
            // widget->show();
            // hLayout->addStretch();
            // hLayout->addWidget(widget);
            // connect(widget,SIGNAL(currentChanged(int)),this,SLOT(on_tab_change(int)));
            if (4 * i + j + 1 > total_num)
            {
                flag = false;
                break;
            }
            CustIListItem *widget = new CustIListItem(widget2);
            widget->set_item(4 * i + j + 1, tr(QString("cup%1").arg(4 * i + j + 1).toLocal8Bit()), QString("/home/uthuqinghong/Desktop/gin-mall-qt/gin-mall-qt-client-1.0.0/cup_res/cup%1.jpg").arg(4 * i + j + 1));
            // widget->show();
            hLayout->addStretch(1);
            hLayout->addWidget(widget);
        }
        // 不够整行时，做一个近似的对齐．待后续使用qtablewidget改造
        if (flag)
        {
            hLayout->addStretch(1);
        }
        else
        {
            hLayout->addStretch(8);
        }
        // hLayout->setMargin(0);
        // hLayout->setSpacing(10);

        // QWidget *widget2 = new QWidget(this);
        widget2->setLayout(hLayout);
        widget2->show();
        QListWidgetItem *item = new QListWidgetItem();
        // 设置item的大小，大小应该比每个item
        item->setSizeHint(QSize(this->width(), 150));
        // 取消选中，否则点击时会选中整行
        item->setFlags(item->flags() & ~Qt::ItemIsSelectable);
        product_listWidget->addItem(item);
        product_listWidget->setItemWidget(item, widget2);
    }
}

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
    ui->tabWidget->setFixedSize(QSize(850, 800));
    this->setFixedSize(QSize(850, 900));

    this->setStyleSheet("background-color:white;");
    QWidget *scroll_widget = new QWidget(ui->first_tab);
    QVBoxLayout *vLayout = new QVBoxLayout;
    CarouselImageWidget *carousel_img = new CarouselImageWidget(scroll_widget);
    ui->first_tab->setStyleSheet("background-color:white;");
    // CarouselImageWidget *carousel_img = ui->first_tab->findChild<CarouselImageWidget *>("carousel_img_widget");
    carousel_img->addImage("/home/uthuqinghong/Desktop/gin-mall-qt/gin-mall-qt-client-1.0.0/carousel_img_res/1.jpg");
    carousel_img->addImage("/home/uthuqinghong/Desktop/gin-mall-qt/gin-mall-qt-client-1.0.0/carousel_img_res/2.jpg");
    carousel_img->addImage("/home/uthuqinghong/Desktop/gin-mall-qt/gin-mall-qt-client-1.0.0/carousel_img_res/3.jpg");
    carousel_img->addImage("/home/uthuqinghong/Desktop/gin-mall-qt/gin-mall-qt-client-1.0.0/carousel_img_res/4.jpg");
    carousel_img->addImage("/home/uthuqinghong/Desktop/gin-mall-qt/gin-mall-qt-client-1.0.0/carousel_img_res/5.jpg");
    carousel_img->setControlButtonColor(Qt::yellow);
    carousel_img->setBorderColor(Qt::red);
    carousel_img->setImageChangeDuration(2000);
    carousel_img->startPlay();
    vLayout->addWidget(carousel_img);
    QLabel *list_label = new QLabel(scroll_widget);
    list_label->setText(tr("推荐"));
    vLayout->addWidget(list_label);
    // qInfo() << "tttttttttttttttttttt height:" << carousel_img->height() << ", width:" << carousel_img->width();

    // 增加滚动条
    product_listWidget = new QListWidget(scroll_widget);
    init_product_info(product_listWidget);
    // QListWidget不显示边框
    product_listWidget->setFrameShape(QListWidget::NoFrame);
    // QListWidget不显示滚动条
    product_listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    product_listWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    vLayout->addWidget(product_listWidget);

    QWidget *page_info_widget = new QWidget(scroll_widget);

    QHBoxLayout *pageInfoLayout = new QHBoxLayout;
    QPushButton *pre_btn = new QPushButton(page_info_widget);
    QPushButton *next_btn = new QPushButton(page_info_widget);
    pre_btn->setText("<");
    next_btn->setText(">");
    page_label = new QLabel(page_info_widget);
    // page_label->setText(QString("1/1"));
    page_label->setText(QString("%1/%2").arg(m_current_page).arg(total_page));
    pageInfoLayout->addStretch();
    pageInfoLayout->addWidget(pre_btn);
    pageInfoLayout->addWidget(next_btn);
    pageInfoLayout->addWidget(page_label);
    page_info_widget->setLayout(pageInfoLayout);
    page_info_widget->setFixedWidth(850);
    pageInfoLayout->addStretch();

    vLayout->addWidget(page_info_widget);

    scroll_widget->setLayout(vLayout);
    scroll_widget->setFixedSize(QSize(850, 800));

    this->setWindowTitle(tr("Shopping Mall"));
    // 窗体没有最大化最小化按钮
    this->setWindowFlag(Qt::Dialog);
    // 隐藏最大最小化
    // this->setWindowFlags(this->windowFlags()&~Qt::WindowMinMaxButtonsHint);
    // 窗口可以最小化，但不能最大化
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowMinMaxButtonsHint | Qt::WindowMinimizeButtonHint);
    // 窗口固定大小，禁止拖动右下角改变大小
    setFixedSize(this->width(), this->height());

    QScrollArea *m_pScroll = new QScrollArea(this);
    // 给centralwidget设置滚动条
    m_pScroll->setWidget(scroll_widget);
    // 隐藏竖向滚动条
    // m_pScroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // 隐藏横向滚动条
    m_pScroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // 这里注意，要比主窗体的尺寸要大，不然太小的话会留下一片空白
    // ui->centralwidget->setMinimumSize(1500,1000);

    QVBoxLayout *pLayout = new QVBoxLayout;
    pLayout->addWidget(m_pScroll);
    pLayout->setMargin(0);
    pLayout->setSpacing(0);
    ui->first_tab->setLayout(pLayout);

    // 不显示状态栏
    ui->statusbar->hide();

    connect(ui->tabWidget, SIGNAL(currentChanged(int)), this, SLOT(on_tab_change(int)));
    connect(ui->search_btn, SIGNAL(clicked()), this, SLOT(on_search_btn_clicked()));

    connect(pre_btn, SIGNAL(clicked()), this, SLOT(on_pre_btn_clicked()));
    connect(next_btn, SIGNAL(clicked()), this, SLOT(on_next_btn_clicked()));
    // connect(ui->user_info_comboBox, SIGNAL(currentTextChanged(const QString &text)), this, SLOT(on_comboBox_currentIndexChanged(const QString &arg)));
}

void Home::on_pre_btn_clicked()
{
    qInfo() << "on_pre_btn_clicked";
    if (m_current_page <= 1)
    {
        return;
    }
    product_listWidget->clear();
    m_current_page--;
    set_listwidget(m_current_page);
    page_label->setText(QString("%1/%2").arg(m_current_page).arg(total_page));
}

void Home::on_next_btn_clicked()
{
    qInfo() << "on_next_btn_clicked";
    if (m_current_page >= total_page)
    {
        return;
    }

    product_listWidget->clear();
    m_current_page++;
    set_listwidget(m_current_page);
    page_label->setText(QString("%1/%2").arg(m_current_page).arg(total_page));
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
    // ui->tabWidget->setCurrentIndex(index);
    // 获取发射信号的对象
    // QPushButton* btn = qobject_cast<QPushButton*>(sender());
}

void Home::on_search_btn_clicked()
{
    qInfo() << "tttttttttttttttttttt on_search_btn_clicked";
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
