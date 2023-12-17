#include "Blackjack.h"
#include <iostream>

GameResult Blackjack::play(Deck& deck) {
    dealer.resetHand();
        player.resetHand();

        deck.shuffle(); // Перемешиваем существующую колоду перед каждым раундом  

        dealer.drawCard(deck);

        std::cout << "The dealer is showing: " << dealer.score() << '\n';

        player.drawCard(deck);
        player.drawCard(deck);

        if (playerTurn(deck, player)) {
            return GameResult::DealerWon;
        }

        if (dealerTurn(deck, dealer)) {
            return GameResult::PlayerWon;
        }
        if (player.score() == dealer.score()) {
            return GameResult::IsTie;
        }

        return player.score() > dealer.score() ? GameResult::PlayerWon : GameResult::DealerWon;
}

bool Blackjack::isBust() {
    return player.score() > maximumScore || dealer.score() > maximumScore;
}

bool Blackjack::playerTurn(Deck& deck, Player& player) {
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

bool Blackjack::dealerTurn(Deck& deck, Player& dealer) {
    while (dealer.score() < minimumDealerScore) {
            dealer.drawCard(deck);
        }
        std::cout << "The dealer is showing: " << dealer.score() << '\n';
        return isBust();
}
