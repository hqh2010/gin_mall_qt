#include "accountmanage.h"
#include "ui_accountmanage.h"

#include "model/data/data_def.h"
#include "utils/common/common.h"
#include <QMouseEvent>
#include <QMessageBox>
#include <QFileDialog>
#include <QLineEdit>

extern UserInfo current_user;

AccountManage::AccountManage(QWidget *parent) : QMainWindow(parent),
                                                ui(new Ui::AccountManage)
{
    ui->setupUi(this);

    QWidget *centralWidget = new QWidget(this);
    QGridLayout *layout = new QGridLayout();

    centralWidget->setLayout(layout); //qt添加控件方法，qt窗口添加按钮，qt添加按钮，qt添加layout

    img = new QLabel;
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
        pixmap = pixmap.scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        img->setPixmap(pixmap);
        // 设置图片宽度
        img->heightForWidth(200);
    }
    // Add Items to QGridLayout Here
    // Row and Column counts are set Automatically
    layout->addWidget(new QLabel("头像"), 0, 0);
    layout->addWidget(img, 0, 1);

    layout->addWidget(new QLabel(tr("点击头像可以更改新头像")), 1, 1);
    // 后端服务器暂不支持修改昵称功能
    QLineEdit *edit = new QLineEdit;
    edit->setPlaceholderText(tr("请输入昵称"));
    layout->addWidget(new QLabel(tr("昵称")), 2, 0);
    layout->addWidget(edit, 2, 1);
    QPushButton *save_btn = new QPushButton(tr("保存"));
    layout->addWidget(save_btn, 3, 0);
    QPushButton *cancel_btn = new QPushButton(tr("取消"));
    layout->addWidget(cancel_btn, 3, 1);

    setCentralWidget(centralWidget);

    // 开启悬停事件
    img->setAttribute(Qt::WA_Hover, true);
    // 安装事件过滤器
    img->installEventFilter(this);

    this->setWindowTitle(tr("帐户管理"));
    // 窗体没有最大化最小化按钮
    this->setWindowFlag(Qt::Dialog);
    // 隐藏最大最小化
    // this->setWindowFlags(this->windowFlags()&~Qt::WindowMinMaxButtonsHint);
    // 窗口可以最小化，但不能最大化
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowMinMaxButtonsHint | Qt::WindowMinimizeButtonHint);
    // 窗口固定大小，禁止拖动右下角改变大小
    setFixedSize(459, 459);
    // connect(img, SIGNAL(clicked()), this, SLOT(onImgButtonClicked()));
}

void AccountManage::onImgButtonClicked()
{
    qInfo() << "onImgButtonClicked";
    qInfo() << QDir::home().path();
    QString fileName = QFileDialog::getOpenFileName(
        this,
        tr("请选择一张图片"),
        QString("%1/Pictures").arg(QDir::home().path()),
        tr("images(*.png *jpg)"));
    if (fileName.isEmpty())
    {
        QMessageBox::warning(this, "Warning!", "Failed to open the file!");
        return;
    }
    else
    {
        QPixmap pixmap;
        // 加载默认图片
        pixmap.load(fileName);
        // QPixmap pixmap("http://10.20.6.68:3000/static/imgs/avatar/avatar.JPG");
        pixmap = pixmap.scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        img->setPixmap(pixmap);
        // 设置图片宽度
        img->heightForWidth(200);

        // 上传图片到服务器
        QString out = "";
        QString err_info = "";
        QMap<QString, QString> mapData;
        QStringList imglist;
        imglist.push_back(fileName);
        qInfo() << "onImgButtonClicked fileName:" << fileName << ", token:" << current_user.token;
        int ret = HTTPCLIENT->post_file(AVATAR, mapData, imglist, current_user.token, out, err_info);
        // ret |= utils::load_from_json(out, current_user, err_info);
        // qInfo() << "load_from_json ret:" << ret << current_user.nickname << ", token:" << current_user.token;
        qInfo() << "load_from_json ret:" << ret << out;
        if (ret)
        {
            // to do根据服务端状态码来显示错误信息并全球化
            QMessageBox msgBox;
            msgBox.setWindowTitle(tr("警告"));
            // msgBox.setWindowTitle(tr("login_box_title"));
            msgBox.setText(tr(err_info.toLocal8Bit()));
            msgBox.setStandardButtons(QMessageBox::Ok);
            // msgBox.setButtonText(QMessageBox::Ok, tr("login_box_btn"));
            msgBox.setIcon(QMessageBox::Warning);
            msgBox.exec();
            return;
        }
    }
}

bool AccountManage::eventFilter(QObject *obj, QEvent *event)
{
    switch (event->type())
    {
    case QEvent::HoverEnter:
        if (obj == img)
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
        if (obj == img)
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
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        if (mouseEvent->button() == Qt::LeftButton)
        {
            if (obj == img)
            {
                onImgButtonClicked();
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

void AccountManage::closeEvent(QCloseEvent *event)
{
    // 忽略要关闭这个窗口的事件，当前窗口就不会被关闭
    event->ignore();
    emit accountToHomeWin();
}

AccountManage::~AccountManage()
{
    delete ui;
}
