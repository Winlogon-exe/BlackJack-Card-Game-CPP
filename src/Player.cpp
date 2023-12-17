#include "Player.h"

#include <iostream>

void Player::drawCard(Deck& deck) {
    Card drawnCard = deck.drawCard();
    hand.push_back(drawnCard);
    playerScore += static_cast<int>(drawnCard.rank);
}

int Player::score() const {
    return playerScore;
}

bool Player::playerWantsHit() {
     while (true)
        {
            std::cout << "(h) to hit, or (s) to stand: ";

            char ch{};
            std::cin >> ch;

            switch (ch)
            {
            case 'h':
                return true;
            case 's':
                return false;
            }
        }
}

void Player::resetHand() {
    hand.clear();
    playerScore = 0;
}
