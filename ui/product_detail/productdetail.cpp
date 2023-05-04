#include "productdetail.h"
#include "ui_productdetail.h"

#include <QHBoxLayout>
#include <QPushButton>
#include <QCloseEvent>
#include <QDebug>

ProductDetail::ProductDetail(QWidget *parent) : QMainWindow(parent),
                                                ui(new Ui::ProductDetail)
{
    ui->setupUi(this);

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addStretch();
    img = new QLabel;
    QPixmap pixmap;
    pixmap.load("/home/uthuqinghong/Desktop/gin-mall-qt/gin-mall-qt-client-1.0.0/cup_res/cup1.jpg");
    pixmap = pixmap.scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    img->setPixmap(pixmap);
    hlayout->addWidget(img);
    hlayout->addStretch();

    QWidget *right_widget = new QWidget;

    QVBoxLayout *vlayout = new QVBoxLayout;
    QLabel *dsc_label = new QLabel;
    dsc_label->setText(tr("色彩柔和艳丽，图案美观漂亮，晶莹剔透，色彩斑斓，夺人眼球。外观精致，巧夺天工,小巧玲珑,精雕细琢，做工精细，独具匠心。结实耐用，方便携带，设计人性化。"));
    dsc_label->setWordWrap(true);
    dsc_label->adjustSize();
    vlayout->addWidget(dsc_label);

    QLabel *price_label = new QLabel;
    price_label->setText(tr("￥199.0元"));
    price_label->adjustSize();
    vlayout->addWidget(price_label);

    QHBoxLayout *btnlayout = new QHBoxLayout;
    QPushButton *buy_btn = new QPushButton;
    buy_btn->setText(tr("立即购买"));
    QPushButton *cart_btn = new QPushButton;
    cart_btn->setText(tr("加入购物车"));
    connect(cart_btn, SIGNAL(clicked()), this, SLOT(on_cart_btn_clicked()));

    btnlayout->addWidget(cart_btn);
    btnlayout->addWidget(buy_btn);
    QWidget *btn_widget = new QWidget(right_widget);
    btn_widget->setLayout(btnlayout);

    vlayout->addWidget(btn_widget);
    right_widget->setLayout(vlayout);

    hlayout->addWidget(right_widget);
    ui->centralwidget->setLayout(hlayout);

    this->setWindowTitle(tr("商品详情"));
    // 窗体没有最大化最小化按钮
    this->setWindowFlag(Qt::Dialog);
    // 隐藏最大最小化
    // this->setWindowFlags(this->windowFlags()&~Qt::WindowMinMaxButtonsHint);
    // 窗口可以最小化，但不能最大化
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowMinMaxButtonsHint | Qt::WindowMinimizeButtonHint);
    // 窗口固定大小，禁止拖动右下角改变大小
    setFixedSize(500, 400);
}

void ProductDetail::reload(int idx)
{
    QPixmap pixmap;
    pixmap.load(QString("/home/uthuqinghong/Desktop/gin-mall-qt/gin-mall-qt-client-1.0.0/cup_res/cup%1.jpg").arg(idx));
    pixmap = pixmap.scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    img->setPixmap(pixmap);
}

void ProductDetail::on_cart_btn_clicked()
{
    qInfo() << "on_cart_btn_clicked";
    emit addProduct(idx);
}

void ProductDetail::closeEvent(QCloseEvent *event)
{
    // 忽略要关闭这个窗口的事件，当前窗口就不会被关闭
    event->ignore();
    emit productToHomeWin();
}

ProductDetail::~ProductDetail()
{
    delete ui;
}
