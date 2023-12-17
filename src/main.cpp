#include "Blackjack.h"  

#include <algorithm> // std::shuffle
#include <array>
#include <ctime>     // std::time
#include <iostream>
#include <random>    // std::mt19937
#include <vector> 


int main() {
    while (true) {
        Deck deck;
        Blackjack blackJack;
        GameResult result = blackJack.play(deck); 

        switch (result) {
        case GameResult::PlayerWon:
            std::cout << "You win!\n";
            break;
        case GameResult::DealerWon:
            std::cout << "You lose!\n";
            break;
        case GameResult::IsTie:
            std::cout << "Tie!\n";
            break;
        }

        std::cout << "Do you want to play another round? (y/n): ";
        char ch;
        std::cin >> ch;

        if (ch != 'y') {
            break; // Если игрок не хочет играть ещё раз, завершаем игру.
        }
    }
    return 0;
}