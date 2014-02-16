#ifndef CARDLABEL_H
#define CARDLABEL_H
#include <QLabel>
#include <QDebug>
#include <QMouseEvent>
#include <cmath>

class CardLabel: public QLabel
{
    Q_OBJECT
public:
    explicit CardLabel(QWidget*);

    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent*);
    void mouseDoubleClickEvent(QMouseEvent*);

    const int static CARD_WIDTH = 135;
    const int static CARD_HEIGHT = 201;
    QPoint offset;
    int family;
    int number;
    int cid;
    int oid;
    int oldowner;
    bool isOnTopB;
    bool onAir;


    bool isOnTop(){return isOnTopB;}
    void setOnTop(bool val){isOnTopB = val;}
    bool isOnAir(){return onAir;}
    void setOnAir(bool val){onAir = val;}

    bool hasFaceUp(){
        return property("faceup").toBool();
    }
    int getCardID(){
        return cid;
    }
    void setCardID(int id){
        setProperty("cardid", id);
        cid = id;
    }
    void hide(){
        emit showHide(this, false);
        setProperty("faceup", false);
    }
    void show(){
        emit showHide(this, true);
        setProperty("faceup", true);
    }
    void setFamily(int fam){
        setProperty("family", fam);
        family = fam;
    }
    int getFamily(){
       return family;
    }
    int getCardNumber(){
        return number;
    }
    void setCardNumber(int num){
        setProperty("number", num);
        number = num;
    }
    int getOwnerID(){

        return oid;
    }
    void setOwnerID(int id){
        setProperty("ownerid", id);
        oid = id;
    }
    int getOldOwnerID(){

        return oldowner;
    }
    void setOldOwnerID(int id){
        setProperty("oldownerid", id);
        oldowner = id;
    }

    QPoint getCenter(){
        return pos() + QPoint(67,100);
    }

signals:
    void mouseDragged(QMouseEvent*, CardLabel *);
    void mouseMoved(QMouseEvent*, CardLabel *);
    void mouseReleased(QMouseEvent*, CardLabel *);
    void mouseDoubleClick(QMouseEvent*, CardLabel*);
    void showHide(CardLabel*, bool);
};

#endif // CARDLABEL_H
