#ifndef CARDPILE_H
#define CARDPILE_H
#include "../TDA/listpointert.h"
#include <QDebug>
#include "cardlabel.h"
#include <QPoint>

class CardPile: public ListPointerT<CardLabel*>{
public:
    CardPile(QWidget* paren = 0):ListPointerT<CardLabel*>(){parent = paren;}
    const int static CUPS = 0;
    const int static DIAMONDS = 1;
    const int static HEARTS = 2;
    const int static CLOVERS = 3;

    int shown;
    int hidden;
    QPoint startCorner;
    int xc;
    int yc;

    int getX(){return xc;}
    int getY(){return yc;}

    void setX(int p){xc = p;}
    void setY(int p){yc = p;}

    QPoint getCorner(){
        return startCorner;
    }
    void setCorner(QPoint p){

        startCorner = p;
    }

    bool operator==(const CardPile& lhs){
        return (lhs.firstN == firstN && lhs.count == count
                && lhs.xc == xc && lhs.yc == yc);
    }

    bool isEmpty(){
        return getCount() == 0;
    }
    void fixIndexes(){
        NodeT<CardLabel*> *cursor = this->firstN;
        for(int i = 0; i < getCount();i ++){
            if(cursor != 0){
                cursor->value->setCardID(i);
                cursor->value->raise();
            }
            cursor = cursor->next;
        }
    }

    void makeLastOnTop(){
        NodeT<CardLabel*>* cursor = firstN;
        while(cursor != 0){
            cursor->value->setOnTop(false);
            if(cursor->next == 0)
                cursor->value->setOnTop(true);
            cursor = cursor->next;
        }
    }

    void unconverLast(){
        if(count>1){
            get(count-1)->show();
            get(count-1)->setOnTop(true);
        }
    }

    void setAllHidden(){
        NodeT<CardLabel*>* cursor = firstN;
        while(cursor != 0){
            cursor->value->hide();
            cursor = cursor->next;
        }
    }

    void setPileID(int id){
        pileID = id;
    }
    int getPileID(){
        return pileID;
    }

    int pileID;
    QWidget* parent;
};



#endif // CARDPILE_H
