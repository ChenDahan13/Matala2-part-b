#pragma once
#include <iostream> 
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "card.hpp"
using namespace std;
using namespace ariel;


class Player {
    string name;
    vector<Card> stack;
    vector<Card> backupStack;
    int winCount;
    int cardsWon;
    
    public:
        Player(string name = "Chen"): name(std::move(name)), winCount(0), cardsWon(0) {}
        void setWinCount(int winCount);
        void setCardsTaken(int cardsWon);
        Card getCard();
        void throwCard();
        void throwFromBackup();
        bool isStackEmpty();
        bool isBackupStackEmpty();
        Card getCardFromBackup();
        string getName();
        int getWinCount() const{
            return winCount;
        }
        vector<Card> getStack() {
            return stack;
        }
        int stacksize();
        int sizeOfBackupStack();
        int cardesTaken();
        void addCardToStack(Card card);
        void addCardToBackupStack(Card card);
};



