#ifndef CUSTILISTITEM_H
#define CUSTILISTITEM_H

#include <QWidget>
#include <QLabel>

namespace Ui
{
    class CustIListItem;
}

class CustIListItem : public QWidget
{
    Q_OBJECT

public:
    explicit CustIListItem(QWidget *parent = nullptr);
    ~CustIListItem();

    // void mousePressEvent(QMouseEvent* event) override;
    bool eventFilter(QObject *obj, QEvent *event) override;

    void set_item(int id, const QString &icon_dsc, const QString icon_path);

private:
    void init_ui();

private:
    // Ui::CustIListItem *ui;
    QLabel *icon_label;
    QLabel *dsc_label;
    int item_id;
};

#endif // CUSTILISTITEM_H
