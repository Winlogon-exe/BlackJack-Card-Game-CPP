#include "Deck.h"
#include <iostream>

Deck::Deck() {
    for (int suit = static_cast<int>(Suit::Clubs); suit <= static_cast<int>(Suit::Spades); suit++) {
        for (int rank = static_cast<int>(Rank::Six); rank <= static_cast<int>(Rank::Ace); rank++) {
            deck.push_back({ static_cast<Suit>(suit), static_cast<Rank>(rank) });
        }
    }
}

void Deck::shuffle() {
    static std::mt19937 mt{ std::random_device{}() };
    std::shuffle(deck.begin(), deck.end(), mt);
}

Card Deck::drawCard() {
    Card drawnCard = deck.back();
    deck.pop_back();
    return drawnCard;
}

void Deck::print() const {
      for (const Card& card : deck) {
            // Выводим масть и номинал каждой карты
            switch (card.suit) {
            case Suit::Clubs:
                std::cout << "Clubs ";
                break;
            case Suit::Hearts:
                std::cout << "Hearts ";
                break;
            case Suit::Diamonds:
                std::cout << "Diamonds ";
                break;
            case Suit::Spades:
                std::cout << "Spades ";
                break;
            }

            switch (card.rank) {
            case Rank::Six:
                std::cout << "6";
                break;
            case Rank::Seven:
                std::cout << "7";
                break;
            case Rank::Eight:
                std::cout << "8";
                break;
            case Rank::Nine:
                std::cout << "9";
                break;
            case Rank::Ten:
                std::cout << "10";
                break;
            case Rank::Jack:
                std::cout << "Jack";
                break;
            case Rank::Queen:
                std::cout << "Queen";
                break;
            case Rank::King:
                std::cout << "King";
                break;
            case Rank::Ace:
                std::cout << "Ace";
                break;
            }
            std::cout << std::endl;
      }
}
