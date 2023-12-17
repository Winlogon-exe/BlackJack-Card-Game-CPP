#pragma once
#include "Casino.h"

class Blackjack : public Casino {
private:
    int maximumScore = 21;
    int minimumDealerScore = 17;

public:
    GameResult play(Deck& deck) override;
    bool isBust();
    bool playerTurn(Deck& deck, Player& player);
    bool dealerTurn(Deck& deck, Player& dealer);
};
