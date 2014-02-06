/* 
 *
 * File:   listPointer.h
 * Author: jaycespinoza
 *
 * Created on January 29, 2014, 12:51 AM
 */

#ifndef LISTPOINTER_H
#define	LISTPOINTER_H
#include <QString>
class Node{
public:
    QString value;
    Node* next;
};

class ListP{
public:
    ListP(int);
    ListP();
    ~ListP();
    int insert(int,QString);
    QString first();
    QString last();
    QString next(int);
    int remove(int);
    int purge();
    int printList();
    void setSize(int);
    QString get(int);
    int getCount(){return count;}
    int getSize(){return size;}
    Node * goTo(int);
    Node* firstN;
    Node* lastN;

private:
    int size;
    int count;
};

#endif	/* LISTPOINTER_H */

