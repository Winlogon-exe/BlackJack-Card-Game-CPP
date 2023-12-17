#include "Nine.h"
#include <iostream>

GameResult Nine::play(Deck& deck) {
    return GameResult::PlayerWon;
}

bool Nine::isBust() {
    return player.score() > maximumScore;
}

bool Nine::playerTurn(Deck& deck, Player& player) {
    while (true) {
            std::cout << "You have: " << player.score() << '\n';

            if (isBust()) {
                return true;
            }
            else if (player.playerWantsHit()) {
                player.drawCard(deck);
            }
            else {
                return false;
            }
        }
}

bool Nine::dealerTurn(Deck& deck, Player& dealer) {
      while (dealer.score() < minimumDealerScore)
        {
            dealer.drawCard(deck);
        }
        std::cout << "The dealer is showing: " << dealer.score() << '\n';
        return isBust();
}
