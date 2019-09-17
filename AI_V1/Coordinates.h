#ifndef COORDINATES_H
#define COORDINATES_H
#include "LinkedList.h"
class Coordinates {
public:
    int level;
    int row;
    int col;

    Coordinates(){}

    Coordinates(int level,int row,int col) {
        // TODO: Your code here...
        this->level = level;
        this->row = row;
        this->col = col;
    }

};
#endif // COORDINATES_H
