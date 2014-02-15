#ifndef CARDLABEL_H
#define CARDLABEL_H
#include <QLabel>
#include <QDebug>
#include <QMouseEvent>

class CardLabel: public QLabel
{
    Q_OBJECT
public:
    explicit CardLabel(QWidget*);

    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent*);
    void mouseDoubleClickEvent(QMouseEvent*);

    QPoint offset;
    int family;
    int number;
    int cid;
    int oid;
    bool isOnTopB;


    bool isOnTop(){return isOnTopB;}
    void setOnTop(bool val){isOnTopB = val;}

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
        oid = id;
    }
signals:
    void mousePressed(QMouseEvent*, CardLabel *);
    void mouseMoved(QMouseEvent*, CardLabel *);
    void mouseReleased(QMouseEvent*, CardLabel *);
    void mouseDoubleClick(QMouseEvent*, CardLabel*);
    void showHide(CardLabel*, bool);
};

#endif // CARDLABEL_H
