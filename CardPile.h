#ifndef CARDPILE_H
#define CARDPILE_H
#include "../TDA/listpointert.h"
#include <QLabel>

class CardPile: public ListPointerT<QLabel*>, QObject{
public:
    CardPile(int size = 10):ListPointerT<QLabel*>(size){}

    bool isEmpty(){
        return getCount() == 0;
    }
    void fixIndexes(){
        NodeT<QLabel*> *cursor = this->firstN;
        for(int i = 1; i < getCount();i ++){
            if(cursor != 0)
                *cursor->value->setProperty("cardid", i);
            cursor = cursor->next;
        }
    }

private:
    int shown;
    int hidden;
};


#endif // CARDPILE_H
