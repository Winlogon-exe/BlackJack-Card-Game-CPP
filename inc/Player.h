#pragma once
#include "../inc/Deck.h"

class Player {
private:
    int playerScore = 0;
    std::vector<Card> hand;

public:
    void drawCard(Deck& deck);
    int score() const;
    bool playerWantsHit();
    void resetHand();
};