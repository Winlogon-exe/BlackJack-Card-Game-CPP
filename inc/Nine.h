#pragma once
#include "Casino.h"

class Nine : public Casino {
private:
    int maximumScore = 9;
    int minimumDealerScore = 6;

public:
    GameResult play(Deck& deck) override;
    bool isBust();
    bool playerTurn(Deck& deck, Player& player);
    bool dealerTurn(Deck& deck, Player& dealer);
};
