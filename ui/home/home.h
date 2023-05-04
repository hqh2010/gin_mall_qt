#ifndef HOME_H
#define HOME_H

#include <QMainWindow>
#include <QListWidget>
#include <QLabel>

#include "ui/account_manage/accountmanage.h"
#include "ui/product_detail/productdetail.h"
#include "ui/cart/cartwin.h"

namespace Ui
{
    class Home;
}

class Home : public QMainWindow
{
    Q_OBJECT

public:
    explicit Home(QWidget *parent = nullptr);
    ~Home();

    void showEvent(QShowEvent *event) override;

    bool eventFilter(QObject *obj, QEvent *event);
private slots:
    void on_search_btn_clicked();

    void on_user_info_comboBox_currentTextChanged(const QString &arg1);

    void on_tab_change(int index);

    void on_pre_btn_clicked();

    void on_next_btn_clicked();

    void on_account_2_home();

    void on_home_2_product(int index);

    void on_product_2_home();

    void on_cart_2_home();

    void on_cart_label_clicked();

    void on_add_product_2_home(int idx);

private:
    void init_ui();
    void init_product_info(QListWidget *listWidget);
    void set_listwidget(const int current_page);

private:
    Ui::Home *ui;

    QListWidget *product_listWidget;

    QLabel *page_label;

    int m_current_page = 1;

    int total_page = 2;

    AccountManage *account_win = nullptr;
    ProductDetail *product_detail_win = nullptr;

    CartWin *cart_win = nullptr;
};

#endif // HOME_H
