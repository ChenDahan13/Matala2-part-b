#include <iostream>
#include <vector>
#include <string>
#include "player.hpp"
#include "card.hpp"
using namespace std;



class Game {
    Player &p1;
    Player &p2;
    vector<Card> deck;
    string log;
    string lastlog;
    int numOfDraws;
    int numOfTurns;
    public:
        Game(Player &pa1, Player &pa2): p1(pa1), p2(pa2), numOfDraws(0), numOfTurns(0) {
            createDeck();
            shuffleDeck();
            divideDeckToPlayers(); 
        }
        int getNumOfDraws() const{
            return numOfDraws;
        }
        int getNumOfTurns() const{
            return numOfTurns;
        }
        void playTurn();
        void printLastTurn();
        void playAll();
        void printWiner();
        void printLog();
        void printStats();
        void createDeck();
        void shuffleDeck();
        void divideDeckToPlayers();
        void startGameFromBegin();
        bool areEqualPlayers(Player &pa1, Player &pa2);
};

