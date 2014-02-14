#include "cardlabel.h"
#include <QDebug>

CardLabel::CardLabel(QWidget *parent):QLabel(parent)
{
    setEnabled(true);
    cid = 0;
    oid = 0;
    family = 0;
    number = 0;
}

void CardLabel::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
            QPoint diff = event->pos() - offset;
            QPoint newpos = this->pos() + diff;
            this->move(newpos);
    }
}

void CardLabel::mouseReleaseEvent(QMouseEvent *)
{

}

void CardLabel::mouseDoubleClickEvent(QMouseEvent *)
{

}

void CardLabel::mousePressEvent(QMouseEvent *event)
{

    offset = event->pos();
}
