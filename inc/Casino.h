#pragma once
#include "Player.h"

enum class GameResult {
    PlayerWon,
    DealerWon,
    IsTie
};

class Casino {
protected:
    Deck deck;
    Player player;
    Player dealer;

public:
    virtual GameResult play(Deck& deck) = 0;
    virtual bool playerTurn(Deck& deck, Player& player) = 0;
    virtual bool isBust() = 0;
    virtual bool dealerTurn(Deck& deck, Player& dealer) = 0;
};
