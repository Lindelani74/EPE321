#ifndef ADAPTEDNB_H
#define ADAPTEDNB_H
#include <string>
#include "Cards.h"
class AdaptedNB
{
public:

    LinkedList<Cards*> likelihoodTables;
    int numberOfPlayers;

    AdaptedNB(){
        likelihoodTables = LinkedList<Cards*>();
        this->numberOfPlayers = 6;
        for (int i=0;i<21;i++){
            likelihoodTables.insert(i,new Cards());
            for (int j=0;j<this->numberOfPlayers;j++) {
                (*this->likelihoodTables.get(i))->card.insert(j,1.0);
            }
        }
    }

    AdaptedNB(int numberOfPlayers_){
        likelihoodTables = LinkedList<Cards*>();
        this->numberOfPlayers = numberOfPlayers_;
        for (int i=0;i<21;i++){
            likelihoodTables.insert(i,new Cards());
            for (int j=0;j<this->numberOfPlayers;j++) {
                (*this->likelihoodTables.get(i))->card.insert(j,1.0);
            }
        }

    }


    /**
     * Returns a list with prior probabilities of each card
     * Cards are indexed in the same order as they appear
     * in communications protocol
     */
    LinkedList<double> calculateProbabilities(){
        LinkedList<double> probabilities = LinkedList<double>();
        double tmp1 = 0.0;
        double tmp2 = 0.0;
        for (int i=0;i<this->likelihoodTables.size();i++) {
            for (int j=0;j<(*this->likelihoodTables.get(i))->card.size();j++) {
                tmp1+=*(*this->likelihoodTables.get(i))->card.get(j);
            }
            probabilities.insert(probabilities.size(),tmp1);
            tmp2+=tmp1;
            tmp1=0.0;
            if(i==5){
                for (int j=0;j<6;j++) {
                    probabilities.set(j,*probabilities.get(j)/tmp2);
                }
                tmp2=0.0;
            }
            else if(i==11){
                for (int j=6;j<12;j++) {
                    probabilities.set(j,*probabilities.get(j)/tmp2);
                }
                tmp2=0.0;
            }
            else if (i==20) {
                for (int j=12;j<21;j++) {
                    probabilities.set(j,*probabilities.get(j)/tmp2);
                }
                tmp2=0.0;
            }
        }

        return probabilities;
    }

    /**
     * Returns a list with indexes of the Cards with the highest
     * prior probability for each given card type.
     * Card types are indexed in the same order as they appear
     * in communications protocol
     */
    LinkedList<int> maxProbabilityIndex(LinkedList<double> probabilities){
        LinkedList<int> index = LinkedList<int>();
        index.insert(0,0);
        index.insert(1,6);
        index.insert(2,12);
        double tmp1 = 0.0;
        double tmp2 = 0.0;
        for (int i=0;i<6;i++) {
            tmp2 = *probabilities.get(i);
            if(tmp2>tmp1){
                index.set(0,i);
                tmp1 = tmp2;
            }
        }
        tmp1=0.0;
        for(int i=6;i<12;i++){
            tmp2 = *probabilities.get(i);
            if(tmp2>tmp1){
                index.set(0,i);
                tmp1 = tmp2;
            }
        }
        tmp1=0.0;
        for(int i=12;i<21;i++) {
            tmp2 = *probabilities.get(i);
            if(tmp2>tmp1){
                index.set(0,i);
                tmp1 = tmp2;
            }
        }
        return index;
    }

    void updateLikelihoodTables(LinkedList<int> suggestedCards,int playerNumber){
        *(*likelihoodTables.get(*suggestedCards.get(0)))->card.get(playerNumber)+=1.0;
        *(*likelihoodTables.get(*suggestedCards.get(1)))->card.get(playerNumber)+=1.0;
        *(*likelihoodTables.get(*suggestedCards.get(2)))->card.get(playerNumber)+=1.0;
    }

    void updateLikelihoodTables(string person, string weapon, string room,int playerNumber){
        int person_=personToIndex(person),weapon_=weaponToIndex(weapon),room_=roomToIndex(room);
        *(*likelihoodTables.get(person_))->card.get(playerNumber)+=1.0;
        *(*likelihoodTables.get(weapon_))->card.get(playerNumber)+=1.0;
        *(*likelihoodTables.get(room_))->card.get(playerNumber)+=1.0;
    }

    void updateLikelihoodTables(LinkedList<int> suggestedCards,int numberOfPlayersSkipped,int playerNumber){
        playerNumber++;
        for(;numberOfPlayersSkipped>0;numberOfPlayersSkipped--,playerNumber++){
            if(playerNumber<numberOfPlayers){
                *(*likelihoodTables.get(*suggestedCards.get(0)))->card.get(playerNumber)+=1.0;
                *(*likelihoodTables.get(*suggestedCards.get(1)))->card.get(playerNumber)+=1.0;
                *(*likelihoodTables.get(*suggestedCards.get(2)))->card.get(playerNumber)+=1.0;
            }
            else {
                playerNumber%=numberOfPlayers;
                *(*likelihoodTables.get(*suggestedCards.get(0)))->card.get(playerNumber)+=1.0;
                *(*likelihoodTables.get(*suggestedCards.get(1)))->card.get(playerNumber)+=1.0;
                *(*likelihoodTables.get(*suggestedCards.get(2)))->card.get(playerNumber)+=1.0;
            }
        }
    }

    LinkedList<int> suggestionToLinkedList(string person,string weapon,string room){
        LinkedList<int> suggestedCards = LinkedList<int>();
        suggestedCards.insert(0,personToIndex(person));
        suggestedCards.insert(1,weaponToIndex(weapon));
        suggestedCards.insert(2,roomToIndex(room));
        return suggestedCards;
    }

    int personToIndex(string person){
        int index = 0;
        if(person=="Scarlet"){
            //index = 0; (stubbed) The index is already set to 0
        }
        else if (person=="Plum") {
            index = 1;
        }
        else if (person=="Peacock") {
            index = 2;
        }
        else if (person=="Green") {
            index = 3;
        }
        else if (person=="Mustard") {
            index = 4;
        }
        else if (person=="White") {
            index = 5;
        }
        else {
            /**error: Function will only execute else if the server
             *        sends incorrect character name
             */
            index = -1;
        }
        return index;
    }

    int weaponToIndex(string weapon){
        int index = 6;
        if(weapon=="Candlestick"){
            //index = 0; (stubbed) The index is already set to 0
        }
        else if (weapon=="Knife") {
            index = 7;
        }
        else if (weapon=="Lead Pipe") {
            index = 8;
        }
        else if (weapon=="Revolver") {
            index = 9;
        }
        else if (weapon=="Rope") {
            index = 10;
        }
        else if (weapon=="Spanner") {
            index = 11;
        }
        else {
            /**error: Function will only execute else if the server
             *        sends incorrect weapon name
             */
            index = -1;
        }
        return index;
    }

    int roomToIndex(string room){
        int index = 12;
        if(room=="Bedroom"){
            //index = 0; (stubbed) The index is already set to 0
        }
        else if (room=="Bathroom") {
            index = 13;
        }
        else if (room=="Study") {
            index = 14;
        }
        else if (room=="Kitchen") {
            index = 15;
        }
        else if (room=="Dining Room") {
            index = 16;
        }
        else if (room=="Living Room") {
            index = 17;
        }
        else if (room=="Courtyard") {
            index = 18;
        }
        else if (room=="Garage") {
            index = 19;
        }
        else if (room=="Games Room") {
            index = 20;
        }
        else {
            /**error: Function will only execute else if the server
             *        sends incorrect weapon name
             */
            index = -1;

        }
        return index;
    }

    string indexToRoom(int roomIndex){
        switch (roomIndex) {
            case 12: return "Bedroom";

            case 13: return "Bathroom";

            case 14: return "Study";

            case 15: return "Kitchen";

            case 16: return "Dining Room";

            case 17: return "Living Room";

            case 18: return "Courtyard";

            case 19: return "Garage";

            case 20: return "Games Room";

            default: return "";

        }
    }

    string indexToWeapon(int roomIndex){
        switch (roomIndex) {
            case 6: return "Candlestick";

            case 7: return "Knife";

            case 8: return "Lead Pipe";

            case 9: return "Revolver";

            case 10: return "Rope";

            case 11: return "Spanner";

            default: return "";

        }
    }

    string indexToPerson(int roomIndex){
        switch (roomIndex) {
            case 0: return "Scarlet";

            case 1: return "Plum";

            case 2: return "Peacock";

            case 3: return "Green";

            case 4: return "Mustard";

            case 5: return "White";

            default: return "";

        }
    }

};
#endif // ADAPTEDNB_H
