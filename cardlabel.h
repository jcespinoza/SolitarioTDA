#ifndef CARDLABEL_H
#define CARDLABEL_H
#include <QLabel>
#include <QMouseEvent>

class CardLabel: public QLabel
{
public:
    CardLabel(QWidget*);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    QPoint offset;
    int family;
    bool hasFaceUp(){
        return property("faceup").toBool();
    }
    int getCardID(){
        return property("cardid").toInt();
    }
    void hide(){
        setProperty("faceup", false);
    }
    void show(){
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
Q_SIGNALS:


};

#endif // CARDLABEL_H
