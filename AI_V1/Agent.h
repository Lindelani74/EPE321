#ifndef AGENT_H
#define AGENT_H
#include "Graph.h"
#include "AdaptedNB.h"
class Agent{
public:
    static Graph map;
    AdaptedNB strategy;
    LinkedList<string> hand;
    LinkedList<string> faceUpCards;
    int playerNumber;
    int mode;

    Agent(){
        mode = 0;
        LinkedList<string> hand= LinkedList<string>();
        LinkedList<string> faceUpCards= LinkedList<string>();
        strategy = AdaptedNB(6);
    }

    Agent(int playerNumber_,int numberOfPlayers){
        mode = 0;
        playerNumber = playerNumber_;
        LinkedList<string> hand= LinkedList<string>();
        LinkedList<string> faceUpCards= LinkedList<string>();
        strategy = AdaptedNB(numberOfPlayers);
    }

    void updateNumberOfPlayers(int numberOfPlayers_){
        strategy.numberOfPlayers = numberOfPlayers_;
    }

    void updatePlayerNumber(int playersNumber_){
        playerNumber = playersNumber_;
    }

};

#endif // AGENT_H
