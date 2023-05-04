#include "checkboxheaderview.h"

CheckBoxHeaderView::CheckBoxHeaderView(int checkColumnIndex, QPoint topLeft, QSize size, Qt::Orientation orientation, QWidget *parent) : QHeaderView(orientation, parent)
{
    checkColIndex = checkColumnIndex;
    this->topLeft = topLeft;
    boxSize = size;
    isChecked = false;
}

void CheckBoxHeaderView::setCheckState(bool state)
{
    isChecked = state;
}


void CheckBoxHeaderView::paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const
{
    painter->save();
    QHeaderView::paintSection(painter, rect, logicalIndex);
    painter->restore();
    if (logicalIndex == checkColIndex)
    {
        QStyleOptionButton option;
        option.rect = QRect(topLeft.x(), topLeft.y(), boxSize.width(), boxSize.height());
        if (isChecked)
        {
            option.state = QStyle::State_On;
        }
        else
        {
            option.state = QStyle::State_Off;
        }
        //加入复选框，设置样式
        QCheckBox *check = new QCheckBox;
        QString sheet = QString("QCheckBox::indicator {width: %1px;  height: %2px;}").arg(boxSize.width()).arg(boxSize.height());
        check->setStyleSheet(sheet);
        this->style()->drawControl(QStyle::CE_CheckBox, &option, painter, check);
    }
}

void CheckBoxHeaderView::mousePressEvent(QMouseEvent *event)
{
    if (visualIndexAt(event->pos().x()) == checkColIndex)
    {
        isChecked = !isChecked;
        this->updateSection(checkColIndex);
        emit signalCheckStateChanged(isChecked);
    }
    //继承后此信号必须手动发送，否则无法响应
    emit QHeaderView::sectionClicked(visualIndexAt(event->pos().x()));
    QHeaderView::mousePressEvent(event);
}
