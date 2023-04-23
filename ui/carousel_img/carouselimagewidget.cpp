#include "carouselimagewidget.h"
#include "ui_carouselimagewidget.h"

#include <QButtonGroup>
#include <QDebug>
#include <QGraphicsDropShadowEffect>
#include <QHBoxLayout>
#include <QLabel>
#include <QPainter>

CarouselImageWidget::CarouselImageWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CarouselImageWidget)
  , m_currentDrawImageIndx(0)
  , m_isShowBorder(false)
  , m_borderColor(Qt::red)
  , m_buttonBackColor(Qt::white)
  , m_borderWidth(5)
  , m_borderRadian(3)
  , m_imageChangeDuration(2000)
{
    // 设置透明，否则左边的产品信息说明看不到
    // this->setStyleSheet(".QWidget{background:transparent;}");
    this->setStyleSheet("background-color:white;");
    ui->setupUi(this);

    initAnimation();
    // 按钮BackWidget;
    m_buttonBackWidget = new QWidget;
    m_buttonBackWidget->setStyleSheet(".QWidget{background:transparent;}");
    // this->setFixedSize(QSize(550, 650));
    this->setFixedSize(QSize(850, 650));
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_TranslucentBackground);

    // 产品信息说明widget
    m_productWidget = new QWidget;
    m_productWidget->setStyleSheet(".QWidget{background:transparent;}");
}

CarouselImageWidget::~CarouselImageWidget()
{
    delete ui;
}

void CarouselImageWidget::initAnimation()
{
    // 添加ImageOpacity属性;
    this->setProperty("ImageOpacity", 1.0);
    // 动画切换类;
    m_opacityAnimation = new QPropertyAnimation(this, "ImageOpacity");
    // 这里要设置的动画时间小于图片切换时间;
    m_opacityAnimation->setDuration(m_imageChangeDuration - 200);
    m_opacityAnimation->setEasingCurve(QEasingCurve::InOutQuart);
    // 设置ImageOpacity属性值的变化范围;
    m_opacityAnimation->setStartValue(1.0);
    m_opacityAnimation->setEndValue(0.0);
    // 透明度变化及时更新绘图;
    connect(m_opacityAnimation, SIGNAL(valueChanged(const QVariant&)), this, SLOT(update()));
    // 设置图片切换时钟槽函数;
    connect(&m_imageChangeTimer, SIGNAL(timeout()), this, SLOT(onImageChangeTimeout()));
}

void CarouselImageWidget::initChangeImageButton()
{
    // 注意图片过多按钮可能放置不下;
    QButtonGroup* changeButtonGroup = new QButtonGroup;
    QHBoxLayout* hLayout = new QHBoxLayout(m_buttonBackWidget);
    // 添加伸缩布局说明 https://blog.csdn.net/liang19890820/article/details/51537246
    hLayout->addStretch();
    for (int i = 0; i < m_imageFileNameList.count(); i++)
    {
        QPushButton* pButton = new QPushButton;
        // 图片指示点
        pButton->setFixedSize(QSize(18, 18));
        pButton->setCheckable(true);
        pButton->setStyleSheet(QString("QPushButton{background:rgb(%1, %2, %3);border-radius:6px;margin:3px;}\
                                QPushButton:checked{border-radius:9px;margin:0px;}").arg(m_buttonBackColor.red()).arg(m_buttonBackColor.green()).arg(m_buttonBackColor.blue()));

        // 禁止获取焦点，否则启动时焦点在按钮上面，看起来很怪
        pButton->setFocusPolicy(Qt::NoFocus);
        changeButtonGroup->addButton(pButton, i);
        m_pButtonChangeImageList.append(pButton);
        hLayout->addWidget(pButton);
    }
    hLayout->addStretch();
    // 设置各个控件之间的上下间距
    hLayout->setSpacing(10);
    // 设置hLayout控件与窗体的左右边距为0
    hLayout->setMargin(0);

    QVBoxLayout* productLayout = new QVBoxLayout(m_productWidget);
    QLabel *desc_label = new QLabel;
    QLabel *price_label = new QLabel;
    QPushButton* buy_btn = new QPushButton;
    // 设置自动换行
    desc_label->setText(tr("骁龙8旗舰处理器，徕卡专业摄像头，超级聚光，120Hz刷新率"));
    desc_label->setFixedWidth(300);
    desc_label->setAlignment(Qt::AlignLeft);
    desc_label->setWordWrap(true);
    desc_label->adjustSize();

    price_label->setText(tr("￥1199"));
    price_label->setFixedWidth(300);

    buy_btn->setText(tr("立即购买"));
    buy_btn->setFixedWidth(300);

    // 将2个label和1个按钮添加到QVBoxLayout中，它们的伸缩系数比是 3:1:1:3:3
    productLayout->addStretch(3);
    productLayout->addWidget(desc_label, 1);
    productLayout->addWidget(price_label, 1);
    productLayout->addWidget(buy_btn, 3);
    productLayout->addStretch(3);
    productLayout->setSpacing(0);
    productLayout->setMargin(0);
    m_productWidget->setFixedWidth(300);
    m_productWidget->setFixedHeight(650);
    // QPalette pal(m_productWidget->palette());

    // 设置背景白色
    // pal.setColor(QPalette::Background, Qt::white);
    // m_productWidget->setAutoFillBackground(true);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addStretch();
    mainLayout->addWidget(m_productWidget);
    mainLayout->addWidget(m_buttonBackWidget);
    mainLayout->setContentsMargins(0, 0, 0, 30);


    connect(changeButtonGroup, SIGNAL(buttonClicked(int)), this, SLOT(onImageSwitchButtonClicked(int)));
    connect(buy_btn, SIGNAL(clicked()),this, SLOT(onBuyButtonClicked()));
}

void CarouselImageWidget::setImageList(QStringList imageFileNameList)
{
    m_imageFileNameList = imageFileNameList;
}

void CarouselImageWidget::addImage(QString imageFileName)
{
    m_imageFileNameList.append(imageFileName);
}

void CarouselImageWidget::startPlay()
{
    // 添加完图片之后，根据图片多少设置图片切换按钮;
    initChangeImageButton();
    if (m_imageFileNameList.count() == 1)
    {
        m_pButtonChangeImageList[m_currentDrawImageIndx]->setChecked(true);
    }
    else if (m_imageFileNameList.count() > 1)
    {
        m_pButtonChangeImageList[m_currentDrawImageIndx]->setChecked(true);
        m_currentPixmap = QPixmap(m_imageFileNameList.at(m_currentDrawImageIndx));
        m_imageChangeTimer.start(m_imageChangeDuration);
        update();
    }
}

void CarouselImageWidget::setControlButtonVisible(bool isVisible)
{
    m_buttonBackWidget->setVisible(isVisible);
}

void CarouselImageWidget::setControlButtonColor(QColor buttonColor)
{
    m_buttonBackColor = buttonColor;
}

void CarouselImageWidget::setBorderVisible(bool isVisible)
{
    m_isShowBorder = isVisible;
}

void CarouselImageWidget::setBorderColor(QColor borderColor)
{
    m_borderColor = borderColor;
}

void CarouselImageWidget::setBorderWidth(int borderWidth)
{
    m_borderWidth = borderWidth;
}

void CarouselImageWidget::setBorderRadian(int borderRadian)
{
    m_borderRadian = borderRadian;
}

void CarouselImageWidget::setImageChangeDuration(int duration)
{
    m_imageChangeDuration = duration;
}

void CarouselImageWidget::onImageChangeTimeout()
{
    // 设置前后的图片;
    m_currentPixmap = QPixmap(m_imageFileNameList.at(m_currentDrawImageIndx));
    m_currentDrawImageIndx++;
    if (m_currentDrawImageIndx >= m_imageFileNameList.count())
    {
        m_currentDrawImageIndx = 0;
    }
    m_nextPixmap = QPixmap(m_imageFileNameList.at(m_currentDrawImageIndx));

    m_pButtonChangeImageList[m_currentDrawImageIndx]->setChecked(true);

    // 动画类重新开始;
    m_opacityAnimation->start();
}

void CarouselImageWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QRect imageRect = this->rect();

    // 移动后矩形大小不变
    // imageRect.moveLeft(300);
    // 窗口左边预留300px 显示产品说明和价格等信息
    // this->setStyleSheet(".QWidget{background:transparent;}");
    // this->setStyleSheet("background-color:red;");
    // painter.setBrush(Qt::white);
    imageRect.adjust(300, 0, 0, 0);

    // 是否绘制边框;
    if (m_isShowBorder)
    {
        imageRect.adjust(m_borderWidth, m_borderWidth, -m_borderWidth, -m_borderWidth);
    }

    painter.save();
    // 如果图片列表为空，显示默认图片;
    if (m_imageFileNameList.isEmpty())
    {
        // QPixmap backPixmap = QPixmap(":/Resources/CarouselImageBack.png");
        // painter.drawPixmap(imageRect, backPixmap.scaled(imageRect.size()));
        return;
    }
    // 如果只有一张图片;
    else if (m_imageFileNameList.count() == 1)
    {
        QPixmap backPixmap = QPixmap(m_imageFileNameList.first());
        painter.drawPixmap(imageRect, backPixmap.scaled(imageRect.size()));
    }
    // 多张图片;
    else if (m_imageFileNameList.count() > 1)
    {
        float imageOpacity = this->property("ImageOpacity").toFloat();
        painter.setOpacity(1);
        painter.drawPixmap(imageRect, m_nextPixmap.scaled(imageRect.size()));
        painter.setOpacity(imageOpacity);
        painter.drawPixmap(imageRect, m_currentPixmap.scaled(imageRect.size()));
    }

    painter.restore();
    if (m_isShowBorder)
    {
        qreal adjustedValue = 1.0 * m_borderWidth / 2;
        painter.setPen(QPen(m_borderColor, m_borderWidth));
        QRectF widgetRect = this->rect();
        painter.drawRoundedRect(widgetRect.adjusted(adjustedValue, adjustedValue, -adjustedValue - 1, -adjustedValue - 1), m_borderRadian, m_borderRadian);
    }
}

void CarouselImageWidget::onImageSwitchButtonClicked(int buttonId)
{
    m_currentDrawImageIndx = buttonId - 1;
    if (m_currentDrawImageIndx == -1)
    {
        m_currentDrawImageIndx = m_imageFileNameList.count() - 1;
    }

    qInfo() << "onImageSwitchButtonClicked select img:" << m_currentDrawImageIndx;
    onImageChangeTimeout();
    m_imageChangeTimer.start(m_imageChangeDuration);
    update();
}

void CarouselImageWidget::onBuyButtonClicked()
{
    qInfo() << "onBuyButtonClicked current img:" << m_currentDrawImageIndx;
}

void CarouselImageWidget::mousePressEvent(QMouseEvent* event)
{
    // 这里可以对当前图片进行点击然后触发每个图片对应的效果;
    // 比如web上好多类似的弹出对应的广告页面等功能;
    emit clicked();
    qInfo() << "mousePressEvent select img:" << m_currentDrawImageIndx;
    return QWidget::mousePressEvent(event);
}
