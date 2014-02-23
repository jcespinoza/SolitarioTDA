#include "cardlabel.h"
#include <QDebug>

CardLabel::CardLabel(QWidget *parent):QLabel(parent)
{
    setEnabled(true);
    cid = 0;
    oid = 0;
    oldowner = 0;
    family = 0;
    number = 0;
    isOnTopB = false;
    onAir = false;
    locked = true;

}

void CardLabel::mouseMoveEvent(QMouseEvent *event)
{
    if(!hasFaceUp()) return;
    if (event->buttons() & Qt::LeftButton){
            QPoint diff = event->pos() - offset;
            int ds = std::sqrt(pow(diff.x(),2) + pow(diff.y(),2));
            QPoint newpos = this->pos() + diff;
            this->move(newpos);
            if(ds > 3 && !isOnAir()){
                setOnAir(true);
                emit mouseDragged(event, this);
            }
            emit mouseMoved(event, this);
    }
}

void CardLabel::mouseReleaseEvent(QMouseEvent *e)
{
    if(!hasFaceUp()) return;
    if(isOnAir())
        emit mouseReleased(e, this);
}

void CardLabel::mouseDoubleClickEvent(QMouseEvent *e)
{
    emit mouseDoubleClick(e, this);
}

void CardLabel::mousePressEvent(QMouseEvent *event)
{
    if(!hasFaceUp()) return;
    if(isOnTop())
        raise();
    offset = event->pos();

}
