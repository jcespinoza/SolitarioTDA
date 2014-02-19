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

    void setX(int p){ xc = p; startCorner.rx() = xc;}
    void setY(int p){ yc = p; startCorner.rx() = yc;}

    QPoint getCorner(){
        return startCorner;
    }

    QPoint getCenter(){ return startCorner + QPoint(67,100);}

    void setCorner(QPoint p){startCorner = p; xc = p.rx(); yc = p.ry();}

    bool operator==(const CardPile& lhs){
        return (lhs.firstN == firstN && lhs.count == count
                && lhs.xc == xc && lhs.yc == yc);
    }

    void fixIndexes(){
        qDebug() << "##Running the method to fix the cards' ids";
        NodeT<CardLabel*> *cursor = this->firstN;
        qDebug() << "Created a cursor pointer. About to enter a cycle that will run" << getCount() << "times";
        for(int i = 0; i < getCount();i ++){
            qDebug() << "Run #" << i;
            qDebug() << "Checking if the cursor is not null";
            if(cursor != 0){
                qDebug() << "It wasnt so its safe to change the card's ID";
                cursor->value->setCardID(i);
                qDebug() << "Changed the card ID to " << i;
                cursor->value->raise();
                qDebug() << "Succesfully set the card on top of the screen";
                cursor = cursor->next;
                qDebug() << "Succesfully changed the cursor to the next node in the list";
            }else{
                qDebug() << "It was null";
            }
        }
        qDebug() << "Method wich fixes the cards' IDs finished##";
    }

    void makeLastOnTop(){
        qDebug() << "##makeLastOnTop method";
        NodeT<CardLabel*>* cursor = firstN;
        while(cursor != 0){
            qDebug() << "Cursor was not null so it entered the loop";
            cursor->value->setOnTop(false);
            qDebug() << "Set the card's OnTop attribute to false";
            if(cursor->next == 0){
                qDebug() << "The next was null so this is the last one in the pile";
                cursor->value->setOnTop(true);
                qDebug() << "Set the ontop attribute to true";
            }
            qDebug() << "NOw lets change the cursor to its next";
            cursor = cursor->next;
        }
        qDebug() << "##makeLastOnTop complete";
    }

    void unconverLast(){
        if(count>=1){
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

    void updatePosFrom(CardLabel* from){
        NodeT<CardLabel*>* frNode = getPointer(from);

        if(frNode == 0)
            return;
        QPoint originalpos = from->pos();
        NodeT<CardLabel*>* cursor = frNode->next;
        while(cursor != 0){
            cursor->value->move(originalpos + QPoint(0,27));
            originalpos = cursor->value->pos();
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
