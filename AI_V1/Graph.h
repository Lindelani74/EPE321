#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
using namespace std;
#include "Vertex.h"

class Graph {
public:
    char cluedoBoard [1][8][13]=
    {
        {
            {'x','x','7','.','x','x','x','x','x','.','9','.','x'},
            {'x','x','.','.','.','.','8','0','.','.','.','.','x'},
            {'x','x','.','.','.','.','x','x','x','.','.','.','.'},
            {'x','x','.','.','.','0','x','x','x','0','.','.','1'},
            {'6','.','.','.','.','.','x','x','x','.','.','.','1'},
            {'5','.','.','.','.','.','x','x','x','.','.','.','.'},
            {'.','.','.','.','.','.','.','0','.','.','.','.','x'},
            {'.','4','x','x','.','.','.','3','.','.','.','2','x'},
        }
    };
    int size;
    LinkedList<Vertex*> nodes;

    Graph() {
        this->size = 0;
        createGraphFrom3DMaze(cluedoBoard);
    }

    void debugFunc(){
        cout <<"Leaving createGraph..."<<endl;
    }

    void createGraphFrom3DMaze(char maze[1][8][13]) {
        int tilePosition=10;
        for(int i=0;i<1;i++){

            for(int j=0;j<8;j++){
                for(int k=0;k<13;k++){
                    if(maze[i][j][k] != 'x'){
                        Vertex* tmp =new Vertex(i,j,k,maze[i][j][k]);
                        tmp->tileIndex=tilePosition;
                        tilePosition++;
                        this->nodes.insert(this->size,tmp);
                        //delete tmp;
                        this->size++;
                        //this->count[i]+=1;
                    }
                }
            }
        }
        //cout<<size<<endl; --confirmed size
        //cout<<nodes.size()<<endl; --confirmed size of nodes
        //cout<< nodes.head->element->coords.level<<","<<nodes.head->element->coords.row<<","<<nodes.head->element->coords.col<<endl;

        for(int x=0;x<this->size;x++){
            Vertex* curr = *nodes.get(x);
            //cout<< "getting vertex "<< x <<" withcoordinates: ["<< curr->coords.level <<","<<curr->coords.row<<","<<curr->coords.col<<"]"<<endl;
            for(int j = -1;j<2;j+=2){
                Vertex* tmp1 = this->getVertex(curr->coords.level,curr->coords.row+j,curr->coords.col);
                Vertex* tmp2 = this->getVertex(curr->coords.level,curr->coords.row,curr->coords.col+j);
                if(tmp1!=nullptr){
                    curr->addNeighbour(tmp1);
                }
                if(tmp2!=nullptr){
                    curr->addNeighbour(tmp2);
                }
            }
        }
    }

    /**
     * Returns the vertex with the given coordinates (level, row, col)
     * If the vertex does not exist, returna nullptr.
     * If the coordinates are out of bounds, returns nullptr.
     */
    Vertex* getVertex(int level, int row, int col) {
        // TODO: Your code here...
        //cout<<"In getVertex"<<endl;
        //cout<< "Looking for coordinates: ["<< level <<","<<row<<","<<col<<"]"<<endl;
        for(int i=0;i<this->size;i++){
            Vertex* tmp = *nodes.get(i);
            //cout<<tmp->coords.level<<","<<tmp->coords.row<<","<<tmp->coords.col<<endl;
            if(level==tmp->coords.level&&row==tmp->coords.row&&col==tmp->coords.col)
                return tmp;
        }
        //cout<< "vertex not found returning null" <<endl;
       return nullptr; // Stub line, you can safely remove when required
    }

    /**
     * Returns the vertex with the given the tile position
     * If the vertex does not exist, returna nullptr.
     * If the coordinates are out of bounds, returns nullptr.
     */
    Vertex* getVertex(int tilePosition){
        Vertex* tmp = *nodes.get(tilePosition-10);
        return tmp;
    }

    Vertex* getEntranceVertex(int tilePosition){
        for(int i=0;i<this->size;i++){
            Vertex* tmp = *nodes.get(i);
            //cout<<tmp->coords.level<<","<<tmp->coords.row<<","<<tmp->coords.col<<endl;
            if(tmp->entrance&&tmp->doorNumber==tilePosition)
                return tmp;
        }
        return nullptr;
    }

    Coordinates* getVertexCoordinates(int tilePosition){
        Coordinates* tmpCoordinates = new Coordinates();
        for(int i=0;i<this->size;i++){
            Vertex* tmp = *nodes.get(i);
            //cout<<tmp->coords.level<<","<<tmp->coords.row<<","<<tmp->coords.col<<endl;
            if(tmp->tileIndex==tilePosition){
                tmpCoordinates->level = tmp->coords.level;
                tmpCoordinates->row = tmp->coords.row;
                tmpCoordinates->col = tmp->coords.col;
                return tmpCoordinates;
            }
        }
        return nullptr;
    }

    /**
     * Return all the vertices in the graph.
     * The vertices in the returned array can be in any order.
     */
    Vertex* getAllVertices(){
        // TODO: Your code here...
        return this->LLTOArray(nodes); // Stub line, you can safely remove when required
    }

    Vertex* LLTOArray(LinkedList<Vertex*> list){
        Vertex* tmp = new Vertex[list.size()];
        for(int i=0;i<list.size();i++){
            tmp[i] = **list.get(i);
        }
        return tmp;
    }

    /**
     * Return the vertices adjacent to the given vertex.
     * The vertices in the array can be in any order.
     * Return an empty array if there are no adjacent vertices.
     * If the vertex does not exist, return null.
     */
    Vertex* getAdjacentVertices(Vertex vertex) {
        // TODO: Your code here...
        Vertex* ver = getVertex(vertex.coords.level,vertex.coords.row,vertex.coords.col);

        if(ver == nullptr) return nullptr;

        //cout<< ver->coords.level<<","<<ver->coords.row<<","<<ver->coords.col<<endl;
        return this->LLTOArray(ver->neighbours); // Stub line, you can safely remove when required
    }

    void clearPred(bool flag){
        for(int i=0;i<this->size;i++){
            Vertex* tmp = *this->nodes.get(i);
            tmp->pred = nullptr;
            tmp->currDist = 1000000;
            if(flag==true)
                tmp->alternatives = LinkedList<Vertex*>();
        }
    }

    /**
     * =============================
     * ===    Shortest Path      ===
     * =============================
     */


    int getLongestPathLength(Coordinates start, Coordinates end) {
        // TODO: Your code here...
        //cout<< "getting longest path length" <<endl;
        Vertex* first = this->getVertex(start.level,start.row,start.col);
        if(first==nullptr) return -1;
        //cout <<"Starting coordinates are valid" <<endl;
        Vertex* target = shortestPath(start,end);
        //cout <<"found shortest path" <<endl;
        if(target==nullptr||target->currDist>1000000) return -1;
        else{
            LinkedList<Vertex*> path = this->predToPath(first,target);
            if(path.size()>2)
                this->alternatePath(first,target,path);
            int max = target->currDist;
            this->clearPred(true);
            return max;
        }
    }

    int getShortestPathLength(Coordinates start, Coordinates end) {
        // TODO: Your code here...
        //cout<< "getting longest path length" <<endl;
        Vertex* first = this->getVertex(start.level,start.row,start.col);
        if(first==nullptr) return -1;
        //cout <<"Starting coordinates are valid" <<endl;
        Vertex* target = shortestPath(start,end);
        if(target==nullptr||target->currDist>1000000){
            return -1;}
        else{
            //cout<<"Converting pred pointers to path array"<<endl;
            //LinkedList<Vertex*> path = LinkedList<Vertex*>(this->predToPath(first,target));
            //cout<<"Converting pred pointers to path array complete"<<endl;
            int max =target->currDist;
            this->clearPred(true);
            return max;
        }
    }

    Vertex* shortestPath(Coordinates start, Coordinates end){
        // Labelled corrected shortest path
        //cout<<"In shortest path"<<endl;
        this->clearPred(false);
        LinkedList<Vertex*> toBeChecked = LinkedList<Vertex*>();
        Vertex* first = this->getVertex(start.level,start.row,start.col);
        first->currDist = 0;
        toBeChecked.insert(0,first);
        //cout<<"Found first vertex"<<endl;
        while(toBeChecked.size()>0){
            unsigned int val = 0;
            Vertex* v = toBeChecked.remove(val);
            for(int i=0;i<v->neighbours.size();i++){
                Vertex* u = *v->neighbours.get(i);
                if(u->currDist>v->currDist+1&&!v->alternatives.find(u)){
                    u->currDist = v->currDist+1;
                    u->pred = v;
                    if(!toBeChecked.find(u))
                        toBeChecked.insert(toBeChecked.size(),u);
                }
            }
        }
        //cout<<"End of while"<<endl;
        Vertex* target = this->getVertex(end.level,end.row,end.col);

        if(target==nullptr||target->currDist>this->size){
            //cout<<"Target not found"<<endl;
            return nullptr; // Stub line, you can safely remove when required
        }
          else{
             //cout<<"Target found and distance is: "<<endl;
             //cout<< target->currDist <<endl;
             return target;

        }
    }
    /**
    *	Modification to the label correcting algorithm.
    *	The method allows for shortest path algorithm to consider different edges
    *	Note: Theres no error checking.
    */
    void alternatePath(Vertex* source,Vertex* target,LinkedList<Vertex*> shortestPath){
        int max = target->currDist;
        for(int i=shortestPath.size()-2;i>0;i--){
            Vertex* tmpCPP1 = *shortestPath.get(i);
            tmpCPP1->addAlternatives(*shortestPath.get(i+1));
            if(this->shortestPath(source->coords,target->coords)!=nullptr){
                if(target->currDist>max){
                    max = target->currDist;
                    LinkedList<Vertex*> tmpShortestPath = this->predToPath(source,target);
                    alternatePath(source,target,tmpShortestPath);
                }
            }
            else{
                Vertex* tmpCPP2 = *shortestPath.get(i);
                tmpCPP2->alternatives.remove(*shortestPath.get(i+1));
                this->shortestPath(source->coords,target->coords);
            }
        }
    }

    /**
     * Return an array of vertices that make up the longest path in order from start to end.
     * The starting vertex should be the first element, and the ending vertex should be the last element.
     * If there is no path, null is returned.
     * If no vertex exists at the given coordinates, null is returned.
     */
    Vertex* getLongestPath(Coordinates start, Coordinates end) {
        // TODO: Your code here...
        Vertex* first = this->getVertex(start.level,start.row,start.col);
        if(first==nullptr)
            return nullptr;
        Vertex* target = shortestPath(start,end);
        if(target==nullptr)
            return nullptr;
        else if(target->currDist==1000000){
          Vertex* tmp = new Vertex[0];
          return tmp;
        }
        else{
          LinkedList<Vertex*> path = this->predToPath(first,target);

          if(path.size()>2)
                  this->alternatePath(first,target,path);

          LinkedList<Vertex*> result = predToPath(first,target);
                this->clearPred(true);
                result.insert(0,first);
                return this->LLTOArray(result);
        }
    }
    /**
    *	Returns the path taken to reach target node from source.
    *	Note: Theres no error checking.
    */
    LinkedList<Vertex*> predToPath(Vertex* source,Vertex* target){
        LinkedList<Vertex*> path = LinkedList<Vertex*>();
        Vertex* tmp = target;
        while(*tmp!=*source){
            //cout<<"looping"<<endl;
            path.insert(0,tmp);
            tmp = tmp->pred;
        }
        //cout<<"returning path"<<endl;
        return path;
    }

    //int[] count = {0,0,0};

};
#endif // GRAPH_H
