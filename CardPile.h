#ifndef CARDPILE_H
#define CARDPILE_H
#include "../TDA/listpointert.h"
#include <QLabel>

class CardPile: public ListPointerT, QObject{
public:
    CardPile(int size = 10):ListPointerT<QLabel*>(size){}
    bool isEmpty(){
        return getCount() == 0;
    }
};


#endif // CARDPILE_H
