#include "aboutappwidget.h"
#include "ui_aboutappwidget.h"

AboutAppWidget::AboutAppWidget(QWidget *parent) : QWidget(parent),
                                                  ui(new Ui::AboutAppWidget)
{
    ui->setupUi(this);

    ui->title_label->setText(tr("关于我们"));
    ui->dsc_label->setText(tr("本项目是基于qt的一个电子商城的学习练手的项目，\n欢迎各位踊跃提出意见！"));
    // 设置label换行
    ui->dsc_label->setWordWrap(true);
    // ui->dsc_label->setFixedWidth(320);
    ui->dsc_label->adjustSize();
    ui->front_label->setText(tr("前端"));
    ui->front_label->adjustSize();
    ui->front_addr_label->setText(tr("https://github.com/hqh2010/gin_mall_qt"));
    ui->front_addr_label->adjustSize();
    ui->front_addr_label->setOpenExternalLinks(true);
    // ui->front_addr_label->setText(tr("<a href=\"https://github.com/hqh2010/gin_mall_qt/\">打开CSDN"));
    ui->front_addr_label->setText(tr("<a href=\"https://github.com/hqh2010/gin_mall_qt\">https://github.com/hqh2010/gin_mall_qt"));
    // ui->front_addr_label->setFixedWidth(320);
    ui->rear_label->setText(tr("后端"));
    ui->rear_label->adjustSize();
    ui->rear_addr_label->setText("https://github.com/CocaineCong/gin-mall");
    ui->rear_addr_label->adjustSize();
    ui->rear_addr_label->setOpenExternalLinks(true);
    ui->rear_addr_label->setText(tr("<a href=\"https://github.com/CocaineCong/gin-mall\">https://github.com/CocaineCong/gin-mall"));
    // ui->rear_addr_label->setFixedWidth(320);
    // this->setWindowTitle(tr("关于我们"));
    // 窗口固定大小，禁止拖动右下角改变大小
    setFixedSize(459, 459);
}

AboutAppWidget::~AboutAppWidget()
{
    delete ui;
}
