#pragma once
#include <iostream>
using namespace std;
namespace ariel {
class Card {
    int type; // 1, 2, ..., 13
    string family; // Hearts, diamonds...
    public:
        Card(int type = 1, string family = "Hearts"): type(type), family(std::move(family)) {}
        int getType() const {
            return this->type;
        }
        string getFamily() {
            return this->family;
        }
        string to_string();
        int compareTo(Card &card);

};
}
