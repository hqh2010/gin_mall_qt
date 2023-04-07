#ifndef REGISTER_H
#define REGISTER_H

#include <QMainWindow>

namespace Ui
{
    class Register;
}

class Register : public QMainWindow
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = nullptr);
    ~Register();

    void showEvent(QShowEvent *event) override;
    void closeEvent(QCloseEvent *event) override;
    bool is_from_reg = false;

private:
    Ui::Register *ui;

signals:
    void regToLoginWin();

private slots:
    void on_reg_btn_clicked();

private:
    void init_ui();
};

#endif // REGISTER_H
