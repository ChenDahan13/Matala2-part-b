#include <iostream>
#include <vector>
#include "player.hpp"

string Player::getName() {
    return this->name;
}
int Player::stacksize() {
    return this->stack.size();
}
int Player::sizeOfBackupStack() {
    return this->backupStack.size();
}
int Player::cardesTaken() {
    return this->cardsWon;
}
void Player::setCardsTaken(int cardsWon) {
    this->cardsWon = cardsWon;
}
void Player::setWinCount(int winCount){
    this->winCount = winCount;
}
void Player::addCardToStack(Card card) {
    this->stack.push_back(card);
}
void Player::addCardToBackupStack(Card card) {
    this->backupStack.push_back(card);
}
Card Player::getCard() {
    return this->stack.back();
}
void Player::throwCard() {
    this->stack.pop_back();
}
bool Player::isStackEmpty() {
   return this->stack.empty();
}
void Player::throwFromBackup() {
    this->backupStack.pop_back();
}
bool Player::isBackupStackEmpty() {
    return this->backupStack.empty();
}
Card Player::getCardFromBackup() {
    return this->backupStack.back();
}
