#include "listPointer.h"
#include <iostream>

using namespace std;

ListP::ListP(int size) {
    this->size = size;
    count = 0;
    firstN = 0;
    lastN = 0;
}

ListP::ListP(){
    size = 10;
    count = 0;
    firstN = 0;
    lastN = 0;
}

void ListP::setSize(int i){
    if(i > 0)
        size = i;
    firstN = 0;
    lastN = 0;
}

ListP::~ListP(){
    while(count > 0)
        remove(0);
    lastN = 0;
    delete lastN;
}

QString ListP::first(){
    if(firstN != NULL)
        return firstN->value;
    return -1;
}

int ListP::insert(int pos, QString val){
    if(pos < 0 || pos > count || pos > getSize()
            || count == getSize() || val == 0)
        return -1;
    
        Node* n = new Node();
        n->value = val;
        
    if(pos == 0){
        n->next = firstN;
        firstN = n;
        if(count == pos)
            lastN = firstN;
        count++;
        return 0;
        
    }else if(pos == count){
        n->next = 0;
        lastN->next = n;
        lastN = n;
        count++;
        return 0;
        
    }else{
        Node* cursor = firstN;
        for(int i = 0; i < pos; i++){
            cursor = cursor->next;
            if(cursor == 0){
                return -1;
            }
        }
        n->next = cursor->next;;
        cursor->next = n;
        count++;
        return 0;
    }
}

int ListP::printList(){
    Node* cursor = firstN;
    int i = 0;
    while(cursor != 0){
        cout << "\nelement[" << i++ << "]:" << cursor->value.toStdString();
        cursor = cursor->next;
    }
    return 0;
}

QString ListP::last(){
    if(lastN != 0)
        return lastN->value;
    return -1;
}

QString ListP::next(int pos){
    Node* cursor = goTo(pos+1);
    return (cursor == 0)?0:cursor->value;
}

int ListP::remove(int pos){
    if(pos < 0 || pos > count || pos > size)
        return -1;
    
    if(pos == 0){
        Node* target = firstN;
        if(firstN != 0)
            firstN = firstN->next;
        count--;
        target->next = 0;
        delete target;
        return 0;
        
    }else if(pos == count-1){
        Node* target = firstN;
        Node* targPrev;
        
        while(target-> next != 0){
            targPrev = target;
            target = target->next;
        }
        lastN = targPrev;
        targPrev->next = 0;
        delete target;
        count--;
        return 0;
    }else{
        Node* target = firstN;
        Node* targPrev;
        
        for(int i = 0; i < pos; i++){
            targPrev = target;
            target = target->next;
        }
        targPrev->next = target->next;
        delete target;
        count--;
        return 0;
    }
}

int ListP::purge(){
    int p = 0;
    int q;
    while( p < count -1 ){
        q = p + 1;
        while(q <= count-1){
            cout << "\ncomparing " << get(p).toStdString() << " and " << get(q).toStdString();
            if(get(p) == get(q)){
                cout << "\nThey were equal";
                remove(q);
            }else{
                cout << "\nAdvancing q";
                q++;
            }
        }
        p++;
    }
    return 0;
}

QString ListP::get(int pos){
    if(pos < 0 || pos > count-1 || pos > size)
        return -1;
    Node* cursor = firstN;
    for(int i = 0; i < pos; i++){
        cursor = cursor->next;
    }
    return cursor->value;
}

Node* ListP::goTo(int pos){
    if(pos < 0 || pos > count-1 || pos > size)
        return 0;
    Node* cursor = firstN;
    for(int i = 0; i < pos; i++){
        cursor = cursor->next;
    }
    return cursor;
}
