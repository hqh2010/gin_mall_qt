#ifndef PRODUCTDETAIL_H
#define PRODUCTDETAIL_H

#include <QMainWindow>
#include <QLabel>

namespace Ui
{
    class ProductDetail;
}

class ProductDetail : public QMainWindow
{
    Q_OBJECT

public:
    explicit ProductDetail(QWidget *parent = nullptr);
    ~ProductDetail();

    void closeEvent(QCloseEvent *event);
    // 更新产品信息
    void reload(int idx);
signals:
    void productToHomeWin();

public:
    // 标识产品编号
    int idx;

private:
    Ui::ProductDetail *ui;

    QLabel *img = nullptr;
};

#endif // PRODUCTDETAIL_H
