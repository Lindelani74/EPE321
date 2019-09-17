#ifndef AGENT_H
#define AGENT_H
#include "Graph.h"
#include "AdaptedNB.h"
#include <cmath>
class Agent{
public:
    static Graph map;
    AdaptedNB strategy;
    LinkedList<string> hand;
    LinkedList<string> faceUpCards;
    bool makeSuggestionFlag;
    int currentPosition;
    int playerNumber;
    int mode;
    string character;
    LinkedList<string> lastSuggestion;


    Agent(){
        mode = 0;
        LinkedList<string> hand= LinkedList<string>();
        LinkedList<string> faceUpCards= LinkedList<string>();
        strategy = AdaptedNB(6);
        currentPosition = 0;
    }

    Agent(int playerNumber_,int numberOfPlayers){
        mode = 0;
        playerNumber = playerNumber_;
        LinkedList<string> hand= LinkedList<string>();
        LinkedList<string> faceUpCards= LinkedList<string>();
        currentPosition = 0;
        strategy = AdaptedNB(numberOfPlayers);
    }

    void updateNumberOfPlayers(int numberOfPlayers_){
        strategy.numberOfPlayers = numberOfPlayers_;
    }

    void updatePlayerNumber(int playersNumber_){
        playerNumber = playersNumber_;
    }

    int distanceFromRoom(int destination){
        int distanceFromSource = 0;
        switch (currentPosition) {
            case 0:{
                distanceFromSource = this->map.getShortestPathLength(*map.getVertexCoordinates(19),*map.getVertexCoordinates(destination));
                for (int i=0;i<3;i++) {
                    int tmpDistance;
                    switch (i) {
                    case 0: {
                            tmpDistance = this->map.getShortestPathLength(*map.getVertexCoordinates(36),*map.getVertexCoordinates(destination));
                            break;
                        }
                    case 1:{
                        tmpDistance = this->map.getShortestPathLength(*map.getVertexCoordinates(37),*map.getVertexCoordinates(destination));
                        break;
                    }
                    case 2:{
                        tmpDistance = this->map.getShortestPathLength(*map.getVertexCoordinates(68),*map.getVertexCoordinates(destination));
                        break;
                    }
                    default: "ERROR";

                    }
                    if(tmpDistance<distanceFromSource){
                        distanceFromSource = tmpDistance;
                    }
                }
                return distanceFromSource;
            }
            case 1:{
                distanceFromSource = this->map.getShortestPathLength(*map.getVertexCoordinates(40),*map.getVertexCoordinates(destination));
                int tmpDistance= this->map.getShortestPathLength(*map.getVertexCoordinates(50),*map.getVertexCoordinates(destination));
                if(tmpDistance<distanceFromSource){
                    distanceFromSource = tmpDistance;
                }
                return distanceFromSource;
            }
            case 2:{
                if(currentPosition==7){
                    return 1;
                }
                return distanceFromSource = this->map.getShortestPathLength(*map.getVertexCoordinates(82),*map.getVertexCoordinates(destination));
            }
            case 3:{
                return distanceFromSource = this->map.getShortestPathLength(*map.getVertexCoordinates(78),*map.getVertexCoordinates(destination));
            }
            case 4:{
                if(currentPosition==9){
                    return 1;
                }
                return this->map.getShortestPathLength(*map.getVertexCoordinates(74),*map.getVertexCoordinates(destination));
            }
            case 5:{
                if(currentPosition==4){
                    return 1;
                }
                return distanceFromSource = this->map.getShortestPathLength(*map.getVertexCoordinates(51),*map.getVertexCoordinates(destination));
            }
            case 6:{
                return distanceFromSource = this->map.getShortestPathLength(*map.getVertexCoordinates(41),*map.getVertexCoordinates(destination));
            }
            case 7:{
                if(currentPosition==2||currentPosition==8){
                    return 1;
                }
                return distanceFromSource = this->map.getShortestPathLength(*map.getVertexCoordinates(10),*map.getVertexCoordinates(destination));

            }
            case 8:{
                if(currentPosition==7){
                    return 1;
                }
                return distanceFromSource = this->map.getShortestPathLength(*map.getVertexCoordinates(19),*map.getVertexCoordinates(destination));
            }
            case 9:{
                if(currentPosition==4){
                    return 1;
                }
                return distanceFromSource = this->map.getShortestPathLength(*map.getVertexCoordinates(13),*map.getVertexCoordinates(destination));

            }
            default: "ERROR";

            }
        return -1;
    }

    void makeMove(int diceRoll){
        LinkedList<int> tmpMaxProbability = this->strategy.maxProbabilityIndex(this->strategy.calculateProbabilities());
        int destination = (*tmpMaxProbability.get(2));
        int tmpDistance;
        if(currentPosition<10){
            tmpDistance = distanceFromRoom(destination);
        }
        else {
            tmpDistance = this->map.getShortestPathLength(*map.getVertexCoordinates(currentPosition),*map.getVertexCoordinates(destination));
        }

        if(tmpDistance<=diceRoll-1){
            this->currentPosition = destination;
            this->makeSuggestionFlag = true;
        }
    }

    void receiveCard(string card,int playerNumber_,bool initialHandDealing){
        if(initialHandDealing==true)
            hand.insert(hand.size(),card);
        else{
            int numberOfPlayersSkipped = abs(this->playerNumber-playerNumber_)-1;
            LinkedList<int> tmpSuggestion = LinkedList<int>();
            for (int i=0;i<3;i++) {
                if(i==0)
                    tmpSuggestion.insert(tmpSuggestion.size(),this->strategy.personToIndex(*this->lastSuggestion.get(i)));
                else if (i==1)
                    tmpSuggestion.insert(tmpSuggestion.size(),this->strategy.weaponToIndex(*this->lastSuggestion.get(i)));
                else {
                    tmpSuggestion.insert(tmpSuggestion.size(),this->strategy.roomToIndex(*this->lastSuggestion.get(i)));
                }

            }
            this->strategy.updateLikelihoodTables(tmpSuggestion,numberOfPlayersSkipped,(this->playerNumber)+1);
            clearCardsFromLikelihoodTable(card);
        }
    }

    void broadcastedSuggestionResponse(LinkedList<string> suggestion,int suggestingPlayer,int respondingPlayer){
        int numberOfPlayersSkipped = abs(suggestingPlayer-respondingPlayer)-1;
        LinkedList<int> tmpSuggestion = LinkedList<int>();
        for (int i=0;i<3;i++) {
            if(i==0)
                tmpSuggestion.insert(tmpSuggestion.size(),this->strategy.personToIndex(*suggestion.get(i)));
            else if (i==1)
                tmpSuggestion.insert(tmpSuggestion.size(),this->strategy.weaponToIndex(*suggestion.get(i)));
            else {
                tmpSuggestion.insert(tmpSuggestion.size(),this->strategy.roomToIndex(*suggestion.get(i)));
            }
        }
        this->strategy.updateLikelihoodTables(tmpSuggestion,numberOfPlayersSkipped,suggestingPlayer+1);
    }

    LinkedList<string> makeSuggestion(){
        this->makeSuggestionFlag = false;
        LinkedList<int> tmpMaxProbability = this->strategy.maxProbabilityIndex(this->strategy.calculateProbabilities());
        this->lastSuggestion.clear();
        for (int i=0;i<3;i++) {
            if(i==0)
                this->lastSuggestion.insert(this->lastSuggestion.size(),this->strategy.indexToPerson(*tmpMaxProbability.get(i)));
            else if (i==1)
                this->lastSuggestion.insert(this->lastSuggestion.size(),this->strategy.indexToWeapon(*tmpMaxProbability.get(i)));
            else {
                this->lastSuggestion.insert(this->lastSuggestion.size(),this->strategy.indexToRoom(*tmpMaxProbability.get(i)));
            }
        }
        return lastSuggestion;
    }

    string showCard(LinkedList<string> suggestion){
        for (int i=0;i<suggestion.size();i++) {
            if( this->hand.find(*suggestion.get(i)) ){
                return *suggestion.get(i);
            }
        }
        return "";
    }

    void clearCardsFromLikelihoodTable(LinkedList<string> faceUpCards_){
        for (int i=0;i<faceUpCards_.size();i++) {
            clearCardsFromLikelihoodTable(*faceUpCards_.get(i));
        }
    }

    void clearCardsFromLikelihoodTable(string receivedCard){
        int tmpCardIndex = this->strategy.personToIndex(receivedCard);
        for (int i=1;i<3;i++) {
            if(tmpCardIndex==-1){
                break;
            }
            if(i==1){
                tmpCardIndex = this->strategy.weaponToIndex(receivedCard);
            }
            else{
                tmpCardIndex = this->strategy.personToIndex(receivedCard);
            }
        }
        for (int i=0;i<this->strategy.numberOfPlayers;i++) {
            *(*this->strategy.likelihoodTables.get(tmpCardIndex))->card.get(i)=0.0;
        }

    }

    void updateGraph(){
        /**
         * stubbed, this function still needs to be completed.
         * Function will enable agents to account for current
         * locations of all players so that there will not be
         * more than one agent on a tile unless in a room.
        */
    }

};

#endif // AGENT_H
