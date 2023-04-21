#ifndef HOME_H
#define HOME_H

#include <QMainWindow>

namespace Ui {
class Home;
}

class Home : public QMainWindow
{
    Q_OBJECT

public:
    explicit Home(QWidget *parent = nullptr);
    ~Home();

    void showEvent(QShowEvent *event) override;
private slots:
    void on_search_btn_clicked();

    void on_user_info_comboBox_currentTextChanged(const QString &arg1);

    void on_tab_change(int index);

private:
    void init_ui();

private:
    Ui::Home *ui;
};

#endif // HOME_H
