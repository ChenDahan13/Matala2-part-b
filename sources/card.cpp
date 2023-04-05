#include <iostream>
#include "card.hpp"
using namespace ariel;

string Card::to_string() {
    return std::to_string(type) + " of " + family;
}
int Card::compareTo(Card &card) {
    return this->type - card.type;
}
