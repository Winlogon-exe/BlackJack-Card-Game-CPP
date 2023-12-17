#pragma once
#include "Card.h"
#include <vector>
#include <random>
#include <algorithm>

class Deck {
private:
    std::vector<Card> deck;

public:
    Deck();
    void shuffle();
    Card drawCard();
    void print() const;
};
