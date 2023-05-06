#ifndef PERSONALDETAILWIN_H
#define PERSONALDETAILWIN_H

#include <QMainWindow>

namespace Ui
{
    class PersonalDetailWin;
}

class PersonalDetailWin : public QMainWindow
{
    Q_OBJECT

public:
    explicit PersonalDetailWin(QWidget *parent = nullptr);
    ~PersonalDetailWin();

    void closeEvent(QCloseEvent *event);
signals:
    void personalToHomeWin();
private:
    void init_ui();

private:
    Ui::PersonalDetailWin *ui;
};

#endif // PERSONALDETAILWIN_H
