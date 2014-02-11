#ifndef NODET_H
#define NODET_H

template <class Y>
class NodeT
{
public:
    Y value;
    NodeT<Y>* next;
};

#endif // NODET_H
