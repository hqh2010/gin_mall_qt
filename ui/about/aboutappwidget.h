#ifndef ABOUTAPPWIDGET_H
#define ABOUTAPPWIDGET_H

#include <QWidget>

namespace Ui
{
    class AboutAppWidget;
}

class AboutAppWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AboutAppWidget(QWidget *parent = nullptr);
    ~AboutAppWidget();

private:
    Ui::AboutAppWidget *ui;
};

#endif // ABOUTAPPWIDGET_H
