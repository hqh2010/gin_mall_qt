#include "test.h"
#include "ui_test.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QListWidget>
#include <QLabel>
#include <QDebug>

void Test::init_ui()
{
    // i代表行数
    for (int i = 0; i < 2; i++)
    {
        QHBoxLayout *hLayout = new QHBoxLayout;
        // j 代表列数，每列4个
        for (int j = 0; j < 4; j++)
        {
            QWidget *widget = new QWidget;
            widget->setObjectName(QString("item%1").arg(4 * i + j + 1));
            QVBoxLayout *verLayout = new QVBoxLayout;
            // verLayout->setContentsMargins(0, 0, 0, 0);
            verLayout->setSpacing(10);
            QLabel *icon_label = new QLabel;
            QPixmap pixmap(QString("/home/uthuqinghong/Desktop/gin-mall-qt/gin-mall-qt-client-1.0.0/cup_res/cup%1.jpg").arg(4 * i + j + 1));
            pixmap = pixmap.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            icon_label->setPixmap(pixmap);
            // 点击事件交由父控件处理
            icon_label->setAttribute(Qt::WA_TransparentForMouseEvents);
            verLayout->addWidget(icon_label);
            QLabel *dsc_label = new QLabel;
            dsc_label->setText(tr(QString("cup%1").arg(4 * i + j + 1).toLocal8Bit()));
            // 点击事件交由父控件处理
            dsc_label->setAttribute(Qt::WA_TransparentForMouseEvents);
            verLayout->addWidget(dsc_label);
            widget->setLayout(verLayout);
            widget->show();
            hLayout->addStretch();
            hLayout->addWidget(widget);
            //connect(widget,SIGNAL(currentChanged(int)),this,SLOT(on_tab_change(int)));
        }
        hLayout->addStretch();
        // hLayout->setMargin(0);
        // hLayout->setSpacing(10);

        QWidget *widget2 = new QWidget;
        widget2->setLayout(hLayout);
        widget2->show();
        QListWidgetItem *item = new QListWidgetItem();
        // 设置item的大小，大小应该比每个item
        item->setSizeHint(QSize(this->width(),150));
        // 取消选中，否则点击时会选中整行
        item->setFlags(item->flags() & ~Qt::ItemIsSelectable);
        ui->listWidget->addItem(item);
        ui->listWidget->setItemWidget(item, widget2);
    }
}

Test::Test(QWidget *parent) : QWidget(parent),
                              ui(new Ui::Test)
{
    ui->setupUi(this);
    init_ui();
}

void Test::mousePressEvent(QMouseEvent *event)
{
    QWidget* www = qobject_cast<QWidget*>(sender());//获取发射信号的对象
    QString BtnName= www->objectName();//获取按钮定义的对象名称
    qInfo() << "clicked " << BtnName;
    return QWidget::mousePressEvent(event);
}

Test::~Test()
{
    delete ui;
}
