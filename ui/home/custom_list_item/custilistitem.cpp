#include "custilistitem.h"
// #include "ui_custilistitem.h"
#include <QVBoxLayout>

#include <QMouseEvent>
#include <QDebug>
#include <QApplication>

void CustIListItem::init_ui()
{
    QVBoxLayout *verLayout = new QVBoxLayout;
    verLayout->setSpacing(10);
    this->icon_label = new QLabel;
    // QPixmap pixmap(QString("/home/uthuqinghong/Desktop/gin-mall-qt/gin-mall-qt-client-1.0.0/cup_res/cup%1.jpg").arg(4 * i + j + 1));
    // pixmap = pixmap.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    // icon_label->setPixmap(pixmap);
    // 点击事件交由父控件处理
    this->icon_label->setAttribute(Qt::WA_TransparentForMouseEvents);
    verLayout->addWidget(this->icon_label);
    this->dsc_label = new QLabel;
    // dsc_label->setText(tr(QString("cup%1").arg(4 * i + j + 1).toLocal8Bit()));
    // 点击事件交由父控件处理
    this->dsc_label->setAttribute(Qt::WA_TransparentForMouseEvents);
    verLayout->addWidget(this->dsc_label);
    this->setLayout(verLayout);
    // this->show();
    // 开启悬停事件
    this->setAttribute(Qt::WA_Hover, true);
    // 安装事件过滤器
    this->installEventFilter(this);
}

void CustIListItem::set_item(int id, const QString &icon_dsc, const QString icon_path)
{
    QPixmap pixmap(icon_path);
    pixmap = pixmap.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    icon_label->setPixmap(pixmap);
    dsc_label->setText(icon_dsc);
    item_id = id;
}

// void CustIListItem::mousePressEvent(QMouseEvent* event)
// {
//   if (event->button() == Qt::LeftButton)
//   {
//   }
// }

bool CustIListItem::eventFilter(QObject *obj, QEvent *event)
{
    switch (event->type())
    {
    case QEvent::HoverEnter:
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
        qInfo() << "ttttttttttttttttttttttttttttt";
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        if (mouseEvent->button() == Qt::LeftButton)
        {
            qInfo() << "click the item:" << item_id;
            return true;
        }
        break;
    }
    default:
        break;
    }
    return QWidget::eventFilter(obj, event);
}

CustIListItem::CustIListItem(QWidget *parent) : QWidget(parent) //,
                                                                // ui(new Ui::CustIListItem)
{
    // ui->setupUi(this);
    init_ui();
}

CustIListItem::~CustIListItem()
{
    delete dsc_label;
    delete icon_label;
    // delete ui;
}
