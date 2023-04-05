#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <stdexcept>
#include "game.hpp"
using namespace std;

void Game::playAll() {
    while (!this->p1.isStackEmpty() && !this->p2.isStackEmpty())
    {
        playTurn();
    }
    
}

void Game::playTurn() {
    
    bool check = areEqualPlayers(this->p1, this->p2);
    if(check) {
        throw std::invalid_argument("One player can't play against himself");
        return;
    }   

    if(this->p1.isStackEmpty() && this->p2.isStackEmpty()) {
        throw std::invalid_argument("The stacks are empty");
        return;
    } 
    
    int numOfCardsToAdd = 2; // default adding
    Card firstCard = this->p1.getCard();
    this->p1.addCardToBackupStack(firstCard);
    Card secondCard = this->p2.getCard();
    this->p2.addCardToBackupStack(secondCard);
    int turn = firstCard.compareTo(secondCard);
        
    while(turn == 0) { // draw
        this->numOfTurns++;
        this->numOfDraws++;
        numOfCardsToAdd = numOfCardsToAdd + 2;
        this->lastlog = this->p1.getName() + " played " + firstCard.to_string() + " " + this->p2.getName() +                        
                        " played " + secondCard.to_string() + ". " + " draw.\n";                
        this->log += this->lastlog;
        this->p1.throwCard();
        this->p2.throwCard(); 
            
        /*if(this->p1.isStackEmpty() && this->p2.isStackEmpty()) { // in case after draw no left cards
            numOfCardsToAdd = 2;
            startGameFromBegin();
        }*/

        firstCard = this->p1.getCard();
        this->p1.addCardToBackupStack(firstCard);  
        secondCard = this->p2.getCard();
        this->p2.addCardToBackupStack(secondCard);
        turn = firstCard.compareTo(secondCard);
    }

    if(turn > 0) { // player 1 wins
        int numOfWin = this->p1.getWinCount();
        numOfWin = numOfWin + 1; 
        this->p1.setWinCount(numOfWin);
        int numOfCards = this->p1.cardesTaken();
        numOfCards = numOfCards + numOfCardsToAdd; // adding also cards of draws if exist
        this->p1.setCardsTaken(numOfCards);
        this->numOfTurns++;
        this->p1.throwCard();
        this->p2.throwCard(); 
        this->lastlog = this->p1.getName() + " played " + firstCard.to_string() + " " + this->p2.getName() +
                    " played " + secondCard.to_string() + ". " + this->p1.getName() + " wins.\n";
        this->log += this->lastlog;
    } else { // player 2 wins
        int numOfWin = this->p2.getWinCount();
        numOfWin = numOfWin + 1;
        this->p2.setWinCount(numOfWin);
        int numOfCards = this->p2.cardesTaken();
        numOfCards = numOfCards + numOfCardsToAdd; // adding also cards of draws if exist
        this->p2.setCardsTaken(numOfCards);
        this->numOfTurns++;
        this->p1.throwCard();
        this->p2.throwCard(); 
        this->lastlog = this->p1.getName() + " played " + firstCard.to_string() + " " + this->p2.getName() +
                    " played " + secondCard.to_string() + ". " + this->p2.getName() + " wins.\n";
        this->log += this->lastlog;
    }
}


void Game::printLastTurn() {
    cout << this->lastlog << endl;
}

void Game::printLog() {
    cout << this->log << endl;
}

void Game::printStats() {
    cout << "Number of draws in the game: " << this->numOfDraws << endl;
    double drawRate = ((double)this->numOfDraws / (double)this->numOfTurns)*100;
    cout << "Draw rate: " << drawRate << endl << endl;
    cout << this->p1.getName() << " state:" << endl;
    cout << "Number of winning: " << this->p1.getWinCount() << endl;
    cout << "Number of losing: " << this->numOfTurns - this->numOfDraws - this->p1.getWinCount() << endl;
    cout << "Number of cards that was taken: " << this->p1.cardesTaken() << endl << endl;
    cout << this->p2.getName() << " state:" << endl;
    cout << "Number of winning: " << this->p2.getWinCount() << endl;
    cout << "Number of losing: " << this->numOfTurns - this->numOfDraws - this->p2.getWinCount() << endl;
    cout << "Number of cards that was taken: " << this->p2.cardesTaken() << endl;
}

void Game::printWiner() {
    int player1win = this->p1.getWinCount();
    int player2win = this->p2.getWinCount();
    if(player1win > player2win) {
        cout << this->p1.getName() << " won." << endl;
    }
    else if (player1win < player2win) {
        cout << this->p2.getName() << " won." << endl;
    }
    else {
        throw std::invalid_argument("No winner it's even");
    }
}

void Game::createDeck() {
    for(int i = 1; i <= 13; i++) {
        for(int j = 0; j < 4; j++) {
            if(j==0) {
                Card b(i, "Hearts");
                this->deck.push_back(b);
            }
            if(j==1) {
                Card b(i, "Diamonds");
                this->deck.push_back(b);
            }
            if(j==2) {
                Card b(i, "Spades");
                this->deck.push_back(b);
            }
            if(j==3) {
                Card b(i, "Clubs");
                this->deck.push_back(b);
            }
        }
    }
}

void Game::shuffleDeck() {
    random_device r;
    mt19937 g(r());
    shuffle(this->deck.begin(), this->deck.end(), g);
}

void Game::divideDeckToPlayers() {
    bool b = true;
    while (!this->deck.empty())
    {
        if(b) {
            p1.addCardToStack(this->deck.back());
            this->deck.pop_back();
        }
        else {
            p2.addCardToStack(this->deck.back());
            this->deck.pop_back();
        }
        b = !b;
    }
 }

 void Game::startGameFromBegin() { // in case after draw the players have no cards
    this->numOfDraws = 0;
    this->numOfTurns = 0;

    while(!this->p1.isBackupStackEmpty()) { // puts the cards that were thrown back to the original stack
        this->p1.addCardToStack(this->p1.getCardFromBackup());
        this->p1.throwFromBackup();
    }
    this->p1.setWinCount(0);
    this->p1.setCardsTaken(0);

    while(!this->p2.isBackupStackEmpty()) { // puts the cards that were thrown back to the original stack
        this->p2.addCardToStack(this->p2.getCardFromBackup());
        this->p2.throwFromBackup();
    }
    this->p2.setWinCount(0);
    this->p2.setCardsTaken(0);
    
 }

 bool Game::areEqualPlayers(Player &player1, Player &player2) {
    return &player1 == &player2;
 }
 