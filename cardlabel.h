#ifndef CARDLABEL_H
#define CARDLABEL_H
#include <QLabel>
#include <QMouseEvent>

class CardLabel: public QLabel
{
public:
    CardLabel(QWidget*);
    void CardLabel::mousePressEvent(QMouseEvent *);
    void CardLabel::mouseMoveEvent(QMouseEvent *);
    QPoint offset;
};

#endif // CARDLABEL_H
