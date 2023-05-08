#include "addrmanagerwin.h"
#include "ui_addrmanagerwin.h"
#include <QMouseEvent>
#include <QDebug>

void AddrManagerWin::init_ui()
{
    QHBoxLayout *hlayout = new QHBoxLayout;
    QRadioButton *radio = new QRadioButton;
    radio->setText("");
    hlayout->addWidget(radio);

    // 地址和姓名　电话显示
    QVBoxLayout *vlayout2 = new QVBoxLayout;
    QTextEdit *addr_edit = new QTextEdit;
    // addr_edit->setText(tr("湖北省黄冈市黄州区\n巴河县陈家湾xxx号"));
    addr_edit->setText(tr("湖北省黄冈市黄州区"));
    // cursor和anchor均移至末尾
    QTextCursor cursor = addr_edit->textCursor();
    cursor.clearSelection();
    cursor.movePosition(QTextCursor::EndOfLine);
    QString msg = QString(tr("巴河县陈家湾xxx号"));
    addr_edit->append(msg);
    cursor.setPosition(cursor.position(), QTextCursor::MoveAnchor);
    cursor.setPosition(cursor.position() + msg.length(), QTextCursor::KeepAnchor);
    cursor.select(QTextCursor::WordUnderCursor);
    QTextCharFormat fmt;
    fmt.setForeground(Qt::red);
    fmt.setFont(QFont("Microsoft YaHei", 16));
    cursor.mergeCharFormat(fmt);
    cursor.clearSelection();
    cursor.movePosition(QTextCursor::EndOfLine);

    QLineEdit *phone_edit = new QLineEdit;
    phone_edit->setText(tr("张三 183****8654"));

    // 只读
    addr_edit->setReadOnly(true);
    phone_edit->setReadOnly(true);

    vlayout2->addWidget(addr_edit);
    vlayout2->addWidget(phone_edit);

    QWidget *widget2 = new QWidget;
    widget2->setLayout(vlayout2);

    hlayout->addWidget(widget2);

    addr_edit_switch = new QLabel;
    addr_edit_switch->setText(tr("编辑"));

    // 开启悬停事件
    addr_edit_switch->setAttribute(Qt::WA_Hover, true);
    // 安装事件过滤器
    addr_edit_switch->installEventFilter(this);

    // addr_edit_switch->setStyleSheet("color:red;");
    hlayout->addWidget(addr_edit_switch);

    QWidget *widget = new QWidget;
    widget->setLayout(hlayout);

    QVBoxLayout *vlayout = new QVBoxLayout;
    QListWidget *list = new QListWidget;

    QListWidgetItem *item = new QListWidgetItem();
    // 取消选中，否则点击时会选中整行
    item->setFlags(item->flags() & ~Qt::ItemIsSelectable);
    item->setSizeHint(QSize(this->width(), 150));
    list->addItem(item);
    list->setItemWidget(item, widget);

    vlayout->addWidget(list);

    QPushButton *create_btn = new QPushButton;
    create_btn->setText(tr("新建收货地址"));
    vlayout->addWidget(create_btn);

    ui->centralwidget->setLayout(vlayout);

    this->setWindowTitle(tr("收货地址管理"));
    // 窗体没有最大化最小化按钮
    this->setWindowFlag(Qt::Dialog);
    // 隐藏最大最小化
    // this->setWindowFlags(this->windowFlags()&~Qt::WindowMinMaxButtonsHint);
    // 窗口可以最小化，但不能最大化
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowMinMaxButtonsHint | Qt::WindowMinimizeButtonHint);
    // 窗口固定大小，禁止拖动右下角改变大小
    setFixedSize(850, 600);
}

AddrManagerWin::AddrManagerWin(QWidget *parent) : QMainWindow(parent),
                                                  ui(new Ui::AddrManagerWin)
{
    ui->setupUi(this);
    init_ui();
}

AddrManagerWin::~AddrManagerWin()
{
    delete ui;
}

void AddrManagerWin::on_edit_switch_label_clicked()
{
    qInfo() << "on_edit_switch_label_clicked";
}

bool AddrManagerWin::eventFilter(QObject *obj, QEvent *event)
{
    switch (event->type())
    {
    case QEvent::HoverEnter:
        if (obj == addr_edit_switch)
        {
            addr_edit_switch->setStyleSheet("color:blue;");
            // 设置鼠标样式
            QCursor waitCursor = Qt::PointingHandCursor;
            QApplication::setOverrideCursor(waitCursor);
        }
        break;
    case QEvent::HoverLeave:
        if (obj == addr_edit_switch)
        {
            // QPalette pa;
            // pa.setColor(QPalette::WindowText, Qt::black);
            // QLabel *label = (QLabel *)obj;
            // label->setPalette(pa);
            // addr_edit_switch->setStyleSheet("color:#ff6600;");
            addr_edit_switch->setStyleSheet("color:black;");
            QApplication::restoreOverrideCursor();
        }
        break;
    case QEvent::MouseButtonPress:
    {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        if (mouseEvent->button() == Qt::LeftButton)
        {
            if (obj == addr_edit_switch)
            {
                on_edit_switch_label_clicked();
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
