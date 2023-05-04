#include "cartwin.h"
#include "ui_cartwin.h"
#include <QTableWidgetItem>
#include "checkboxheaderview.h"
#include <QHBoxLayout>

int select_cnt = 0;

CartWin::CartWin(QWidget *parent) : QMainWindow(parent),
                                    ui(new Ui::CartWin)
{
    ui->setupUi(this);

    QVBoxLayout *vLayout = new QVBoxLayout;
    tabInfo = new QTableWidget;

    CheckBoxHeaderView *header = new CheckBoxHeaderView(0, QPoint(10, 5), QSize(20, 20), Qt::Horizontal, this);
    QStringList headerText;
    headerText << "全选"
               << "商品名称"
               << "单价"
               << "数量"
               << "小计"
               << "操作";
    tabInfo->setColumnCount(headerText.count());
    // 设置列标签
    tabInfo->setHorizontalHeaderLabels(headerText);
    tabInfo->setHorizontalHeader(header);
    // tabInfo->setFixedSize(QSize(300,800));
    tabInfo->setFixedWidth(800);
    tabInfo->setFixedHeight(380);
    // ui->centralwidget
    // 设置行和列的大小设为与内容相匹配
    // tabInfo->resizeColumnsToContents();
    tabInfo->resizeRowsToContents();
    // 设置表格内容不可编辑
    tabInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);
    // 不显示垂直方向的表头
    tabInfo->verticalHeader()->setVisible(false);
    // 不显示水平滚动条
    tabInfo->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // 设置表格不可被选中
    tabInfo->setSelectionMode(QAbstractItemView::NoSelection);
    // 设置商品名称列宽
    tabInfo->setColumnWidth(1, 200);
    // 设置数量列宽
    tabInfo->setColumnWidth(3, 200);
    connect(header, &CheckBoxHeaderView::signalCheckStateChanged, [=](bool state)
            {
                qInfo() << "勾选状态:" << state << tabInfo->height();

                for (int i = 0; i < tabInfo->rowCount(); i++)
                {
                    QCheckBox *cb = (QCheckBox *)(tabInfo->cellWidget(i, 0));
                    qInfo() << "勾选状态:" << state << cb;
                    if (cb)
                        cb->setChecked(state);
                }
            });
    // 返回鼠标单击的所在单元格的row和col
    connect(tabInfo, SIGNAL(cellClicked(int, int)), this, SLOT(on_prodcut_clicked(int, int)));

    vLayout->addWidget(tabInfo);

    QWidget *widget2 = new QWidget;
    QHBoxLayout *hLayout = new QHBoxLayout;
    buy_again = new QLabel;
    buy_again->setText(tr("继续购物"));
    // 开启悬停事件
    buy_again->setAttribute(Qt::WA_Hover, true);
    // 安装事件过滤器
    buy_again->installEventFilter(this);

    select_info = new QLabel;
    select_info->setText(QString(tr("共")) + QString("<font color = #4896FA >%1</font>").arg(tabInfo->rowCount()) + QString(tr("件商品，")) +
                         QString(tr("已选择")) + QString("<font color = #4896FA >%1</font>").arg(0) + QString(tr("件")));
    QLabel *total_info = new QLabel;
    total_info->setText(QString(tr("合计：0元")));
    QPushButton *pay_btn = new QPushButton;
    pay_btn->setText(QString(tr("去支付")));
    hLayout->addStretch();
    hLayout->addWidget(buy_again);
    hLayout->addStretch(10);
    hLayout->addWidget(select_info);
    hLayout->addWidget(total_info);
    hLayout->addStretch(1);
    hLayout->addWidget(pay_btn);
    widget2->setLayout(hLayout);

    vLayout->addWidget(tabInfo);
    vLayout->addWidget(widget2);

    // QPushButton *add_row_btn = new QPushButton;
    // add_row_btn->setText(QString(tr("增加一行")));
    // connect(add_row_btn, SIGNAL(clicked()), this, SLOT(on_add_row()));
    // vLayout->addWidget(add_row_btn);

    vLayout->setAlignment(this, Qt::AlignTop);
    ui->centralwidget->setLayout(vLayout);

    this->setWindowTitle(tr("购物车"));
    // 窗体没有最大化最小化按钮
    this->setWindowFlag(Qt::Dialog);
    // 窗口可以最小化，但不能最大化
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowMinMaxButtonsHint | Qt::WindowMinimizeButtonHint);
    // 窗口固定大小，禁止拖动右下角改变大小
    setFixedSize(this->width(), this->height());
}

int count = 1;
void CartWin::on_add_row()
{
    add_to_cart(count);
    count++;
    select_info->setText(QString(tr("共")) + QString("<font color = #4896FA >%1</font>").arg(tabInfo->rowCount()) + QString(tr("件商品，")) +
                         QString(tr("已选择")) + QString("<font color = #4896FA >%1</font>").arg(select_cnt) + QString(tr("件")));
}

void CartWin::add_to_cart(int index)
{
    int iRow = tabInfo->rowCount();
    tabInfo->setRowCount(iRow + 1);
    // 设置行高
    tabInfo->setRowHeight(iRow, 100);
    QCheckBox *cb = new QCheckBox;
    // QWidget *widget = new QWidget;
    // QHBoxLayout *hLayout = new QHBoxLayout();
    // hLayout->setMargin(0);
    //hLayout->addWidget(cb);
    connect(cb, SIGNAL(stateChanged(int)), this, SLOT(on_prodcut_selected(int)));
    // 左对齐
    // hLayout->setAlignment(cb, Qt::AlignVCenter | Qt::AlignLeft);

    // widget->setLayout(hLayout);
    // 添加复选框
    // tabInfo->setCellWidget(iRow, 0, widget);
    tabInfo->setCellWidget(iRow, 0, cb);

    // 添加商品名称
    QHBoxLayout *hLayout1 = new QHBoxLayout();
    QLabel *img = new QLabel;
    QPixmap pixmap;
    pixmap.load(QString("/home/uthuqinghong/Desktop/gin-mall-qt/gin-mall-qt-client-1.0.0/cup_res/cup%1.jpg").arg(index));
    pixmap = pixmap.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    img->setPixmap(pixmap);

    QWidget *widget1 = new QWidget;
    QLabel *dsc_label = new QLabel;
    dsc_label->setText(tr(QString("富光cpu%1杯").arg(index).toLocal8Bit()));
    dsc_label->setWordWrap(true);
    dsc_label->adjustSize();

    hLayout1->addStretch();
    hLayout1->addWidget(img);
    hLayout1->addWidget(dsc_label);
    hLayout1->addStretch();
    widget1->setLayout(hLayout1);
    // 添加产品信息
    tabInfo->setCellWidget(iRow, 1, widget1);

    // 添加单价
    QTableWidgetItem *item = new QTableWidgetItem(tr("￥199元"));
    tabInfo->setItem(iRow, 2, item); //添加到界面
    // 添加数量
    QSpinBox *sb = new QSpinBox;
    sb->setValue(1);
    sb->setObjectName(QString("sb%1").arg(iRow));
    tabInfo->setCellWidget(iRow, 3, sb);
    connect(sb, SIGNAL(valueChanged(int)), this, SLOT(on_product_cnt_change(int)));
    // 添加总价
    QTableWidgetItem *item1 = new QTableWidgetItem(tr("￥199元"));
    tabInfo->setItem(iRow, 4, item1); //添加到界面

    // 添加删除按钮
    QLabel *del_label = new QLabel;
    del_label->setText(tr("删除"));
    tabInfo->setCellWidget(iRow, 5, del_label);

    select_info->setText(QString(tr("共")) + QString("<font color = #4896FA >%1</font>").arg(tabInfo->rowCount()) + QString(tr("件商品，")) +
                         QString(tr("已选择")) + QString("<font color = #4896FA >%1</font>").arg(0) + QString(tr("件")));
}

void CartWin::on_prodcut_selected(int state)
{
    if (state)
    {
        select_cnt++;
    }
    else
    {
        select_cnt--;
    }
    select_info->setText(QString(tr("共")) + QString("<font color = #4896FA >%1</font>").arg(tabInfo->rowCount()) + QString(tr("件商品，")) +
                         QString(tr("已选择")) + QString("<font color = #4896FA >%1</font>").arg(select_cnt) + QString(tr("件")));
}

void CartWin::on_product_cnt_change(int cnt)
{
    QSpinBox *sb = qobject_cast<QSpinBox *>(sender());
    if (sb)
    {
        int iRow = sb->objectName().mid(2).toInt();
        QString total = QString("￥%1元").arg(cnt * 199);
        tabInfo->item(iRow, 4)->setText(tr(total.toLocal8Bit()));
    }
}

void CartWin::on_prodcut_clicked(int x, int y)
{
    // 最后一列表示删除
    if (5 == y)
    {
        tabInfo->removeRow(x);
        QCheckBox *cb = (QCheckBox *)(tabInfo->cellWidget(x, 0));
        if (cb && cb->checkState())
        {
            select_cnt--;
        }
        select_info->setText(QString(tr("共")) + QString("<font color = #4896FA >%1</font>").arg(tabInfo->rowCount()) + QString(tr("件商品，")) +
                             QString(tr("已选择")) + QString("<font color = #4896FA >%1</font>").arg(select_cnt) + QString(tr("件")));
    }
}

bool CartWin::eventFilter(QObject *obj, QEvent *event)
{
    switch (event->type())
    {
    case QEvent::HoverEnter:
        if (obj == buy_again)
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
        if (obj == buy_again)
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
            if (obj == buy_again)
            {
                on_buy_again_clicked();
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

void CartWin::on_buy_again_clicked()
{
    qInfo() << "on_buy_again_clicked";
    emit cartToHomeWin();
}

CartWin::~CartWin()
{
    delete ui;
}
