#ifndef CHECKBOXHEADERVIEW_H
#define CHECKBOXHEADERVIEW_H

#include <QtGui>
#include <QPainter>
#include <QHeaderView>
#include <QStyleOptionButton>
#include <QStyle>
#include <QCheckBox>
#include <QEvent>

class CheckBoxHeaderView : public QHeaderView
{
    Q_OBJECT

public:
    CheckBoxHeaderView(int checkColumnIndex, QPoint topLeft, QSize size, 
    Qt::Orientation orientation, QWidget *parent = nullptr);

protected:
    void paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const;
    void mousePressEvent(QMouseEvent *event);

private:
    int     checkColIndex;  //表头列下标
    QPoint  topLeft;        //勾选框起始屏幕坐标
    QSize   boxSize;        //勾选框大小
    bool    isChecked;      //勾选框状态

public:
    void setCheckState(bool state);             //设置复选框状态

signals:
    void signalCheckStateChanged(bool state);   //勾选状态发生改变信号
};

#endif // CHECKBOXHEADERVIEW_H
