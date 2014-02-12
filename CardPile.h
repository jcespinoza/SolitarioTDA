#ifndef CARDPILE_H
#define CARDPILE_H
#include "../TDA/listpointert.h"
#include <QDebug>
#include <QLabel>


class CardPile: public ListPointerT<QLabel*>{
public:
    CardPile(QWidget* paren = 0, int size = 10):ListPointerT<QLabel*>(size){parent = paren;}
    const int static CUPS = 0;
    const int static DIAMONDS = 1;
    const int static HEARTS = 2;
    const int static CLOVERS = 3;

    int shown;
    int hidden;

    bool isEmpty(){
        return getCount() == 0;
    }
    void fixIndexes(){
        NodeT<QLabel*> *cursor = this->firstN;
        for(int i = 0; i < getCount();i ++){
            if(cursor != 0){
                cursor->value->setProperty("cardid", i);
            }
            cursor = cursor->next;
        }
    }
    void setPileID(int id){
        pileID = id;
    }
    int getPileID(){
        return pileID;
    }

private:
    int pileID;

    QWidget* parent;
};



#endif // CARDPILE_H
