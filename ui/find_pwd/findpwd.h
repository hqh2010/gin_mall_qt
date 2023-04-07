#ifndef FINDPWD_H
#define FINDPWD_H

#include <QMainWindow>

namespace Ui
{
    class FindPwd;
}

class FindPwd : public QMainWindow
{
    Q_OBJECT

public:
    explicit FindPwd(QWidget *parent = nullptr);
    ~FindPwd();

    void closeEvent(QCloseEvent *event) override;

private slots:
    void on_reset_btn_clicked();

signals:
    void pwdToLoginWin();

private:
    Ui::FindPwd *ui;
    void init_ui();
};

#endif // FINDPWD_H
