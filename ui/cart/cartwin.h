#ifndef CARTWIN_H
#define CARTWIN_H

#include <QMainWindow>
#include <QTableWidget>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>

namespace Ui
{
    class CartWin;
}

class CartWin : public QMainWindow
{
    Q_OBJECT

public:
    explicit CartWin(QWidget *parent = nullptr);
    ~CartWin();
    void add_to_cart(int index);

    bool eventFilter(QObject *obj, QEvent *event);

private slots:
    void on_add_row();

    void on_product_cnt_change(int cnt);

    void on_prodcut_clicked(int x, int y);

    void on_prodcut_selected(int state);

private:
    void on_buy_again_clicked();

signals:
    void cartToHomeWin();

private:
    Ui::CartWin *ui;
    QTableWidget *tabInfo;

    // 商品选择信息
    QLabel *select_info;
    // 继续购物
    QLabel *buy_again;
};

#endif // CARTWIN_H
