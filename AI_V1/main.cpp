#include <iostream>

using namespace std;
#include <string>
//#include "LinkedList.h"
//#include "Vertex.h"
#include "Graph.h"
#include "AdaptedNB.h"

int main()
{
//    cout << "Hello World!" << endl;
//    LinkedList<string> tmp;

//    for (int i=10;i>0;i--) {
//        tmp.insert(0,"Salim");
//    }

//    tmp.set(5,"Salim@Index5");

//    Node<string>* tmp3 = tmp.getLeader();
//    tmp3->element = "Gotcha";

//    cout << *tmp.get(0) << endl;

//    LinkedList<string> tmp2(tmp);

//    cout << *tmp2.get(5) << endl;

    char maze1[3][5][5] = {
                {
                    {'x','x','x','x','x'},{'x','.','.','x','x'},{'x','u','x','u','x'},
                    {'x','x','x','.','x'},{'x','x','x','x','x'}
                },
                {
                    {'x','x','x','x','x'},{'x','.','.','.','x'},{'x','d','x','b','x'},
                    {'x','.','.','.','x'},{'x','x','x','x','x'}
                },
                    {
                        {'x','x','x','x','x'},{'x','.','.','.','x'},{'x','x','x','d','x'},{'x','x','x','x','x'},{'x','x','x','x','x'}
                    }
            };

            cout<<"Starting"<<endl;
            Graph test1 = Graph();
            cout<<"Creating graph"<<endl;
            //test1.createGraphFrom3DMaze(maze1);
            //cout<<"Getting there"<<endl;

            Vertex v1(4,5,6,'.');
            Vertex v2(7,8,9,'.');
            Coordinates c = Coordinates(1,2,3);

//            LinkedList<int> list= LinkedList<int>();
//            list.insert(0,1);
//            cout<<list.head->element<<endl;

//            LinkedList<Vertex*> list = LinkedList<Vertex*>();
//            list.insert(0,&v1);
//            list.insert(1,&v2);
//            cout<<list.head->next->element->coords.row<<endl;


            Coordinates source = Coordinates(0,1,2);
            Coordinates target = Coordinates(0,6,2);

            cout << "Longest path from "<<source.level<<","<<source.row<<","<<source.col<<" to "<<target.level<<","<<target.row<<","<<target.col<<endl;
            cout << test1.getShortestPathLength(source,target) <<endl;
            cout << test1.getEntranceVertex(1)->tileIndex <<endl;




            AdaptedNB test2 = AdaptedNB(6);
            cout<<"Testing likelihood table"<<endl;

            cout<< *(*test2.likelihoodTables.get(0))->card.get(0) <<endl;
//            Vertex* path = test1.getLongestPath(source,target);
//            for(int i=0;i<sizeof(path)/sizeof(*path);i++){
//                cout << "Index "<<i<<": "<<path[i].coords.level<<","<<path[i].coords.row<<","<<path[i].coords.col<<endl;
//            }


    return 0;
}
