#ifndef VERTEX_H
#define VERTEX_H

#include <cctype>
#include <cstdlib>
#include <iostream>
using namespace std;
#include "Coordinates.h"
#include "LinkedList.h"

class Vertex{
public:

    Coordinates coords;
    //note on entrance: Indicates whether you can move between levels at this vertex
    bool entrance;
    int doorNumber;
    //note on direction: 1 = up, 0 = bidirection, -1 = down, else = invalid
    //int direction;
    int tileIndex;
    LinkedList<Vertex*> neighbours;
    Vertex *pred = nullptr;
    int currDist = 1000000;
    LinkedList<Vertex*> alternatives;

    Vertex(){
           //this->direction = -2;
           this->entrance = false;
       }

       Vertex(int level,int row,int col) {
           // TODO: Your code here...
           this->coords = Coordinates(level,row,col);
           //this->direction = -2;
           this->entrance = false;
       }

       Vertex(int level, int row, int col,char entrance_) {
           //cout<<"Creating Vertex"<<endl;
           this->coords = Coordinates(level,row,col);
           if(entrance_>='0'&&entrance_<='9'){
               //this->direction = 0;
               this->entrance = true;
               this->doorNumber = int(entrance_)-int('0');
           }
           else{
               //this->direction = -2;
               this->entrance = false;
           }
       }

       void addNeighbour(Vertex* neighbour){
           this->neighbours.insert(this->neighbours.size(),neighbour);
       }

       void addAlternatives(Vertex* alternative_){
           this->alternatives.insert(this->alternatives.size(),alternative_);
       }

       bool operator==(const Vertex &right){
           if(right.coords.level==this->coords.level&&right.coords.row==this->coords.row&&right.coords.col==this->coords.col)
               return true;
           return false;
       }

       bool operator!=(const Vertex &right){
           if(right.coords.level==this->coords.level&&right.coords.row==this->coords.row&&right.coords.col==this->coords.col)
               return false;
           return true;
       }

       void operator=(const Vertex &right){
           this->coords = Coordinates(right.coords.level,right.coords.row,right.coords.col);
           //note on entrance: Indicates whether you can move between levels at this vertex
           this->entrance = right.entrance;
           //note on direction: 1 = up, 0 = bidirection, -1 = down, else = invalid
           this->tileIndex = right.tileIndex;
           this->doorNumber = right.doorNumber;
           this->neighbours = LinkedList<Vertex*>(right.neighbours);
           this->pred = right.pred;
           this->currDist = right.currDist;
           this->alternatives = LinkedList<Vertex*>(right.alternatives);

       }

};
#endif // VERTEX_H
