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
    if(!hasFaceUp()) return;
    if (event->buttons() & Qt::LeftButton){
            QPoint diff = event->pos() - offset;
            QPoint newpos = this->pos() + diff;
            this->move(newpos);
    }
}

void CardLabel::mouseReleaseEvent(QMouseEvent *e)
{
    emit mouseReleased(e, this);
}

void CardLabel::mouseDoubleClickEvent(QMouseEvent *e)
{
    emit mouseDoubleClick(e, this);
}

void CardLabel::mousePressEvent(QMouseEvent *event)
{
    if(!hasFaceUp()) return;
    raise();
    qDebug() << "myID is: " << getCardID() << "Am I on top?" << isOnTop();
    offset = event->pos();
}
