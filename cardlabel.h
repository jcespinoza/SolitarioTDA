#ifndef CARDLABEL_H
#define CARDLABEL_H
#include <QLabel>
#include <QMouseEvent>

class CardLabel: public QLabel
{
    Q_OBJECT
public:
    CardLabel(QWidget*);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent*);
    void mouseDoubleClickEvent(QMouseEvent*);

    QPoint offset;
    int family;
    bool hasFaceUp(){
        return property("faceup").toBool();
    }
    int getCardID(){
        return property("cardid").toInt();
    }
    void setCardID(int id){
        setProperty("cardid", id);
    }
    void hide(){
        emit showHide(this, false);
        setProperty("faceup", false);
    }
    void show(){
        //emit showHide(this, true);
        setProperty("faceup", true);
    }
    void setFamily(int fam){
        setProperty("family", fam);
    }
    int getFamily(){
       return property("family").toInt();
    }
    int getCardNumber(){
        return property("number").toInt();
    }
    void setCardNumber(int num){
        setProperty("number", num);
    }
    int getOwnerID(){
        return property("ownerPile").toInt();
    }
    void setOwnerID(int id){
        setProperty("ownerPile", id);
    }
signals:
    void mousePressed(QMouseEvent*, CardLabel *);
    void mouseMoved(QMouseEvent*, CardLabel *);
    void mouseReleased(QMouseEvent*, CardLabel *);
    void mouseDoubleClick(QMouseEvent*, CardLabel*);
    void showHide(CardLabel*, bool);
};

#endif // CARDLABEL_H
