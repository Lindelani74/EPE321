#ifndef CARDS_H
#define CARDS_H
#include "LinkedList.h"
class Cards{

public:
    LinkedList<double> card;

    Cards(){
        card = LinkedList<double>();
    }
};

#endif // CARDS_H
