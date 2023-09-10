#include <algorithm> // std::shuffle
#include <array>
#include <ctime>     // std::time
#include <iostream>
#include <random>    // std::mt19937
#include <vector>    // Добавляем заголовок для std::vector

enum class Suit {
    Clubs,
    Hearts,
    Diamonds,
    Spades
};
enum class Rank {
    Six = 6,
    Seven = 7,
    Eight = 8,
    Nine = 9,
    Ten = 10,
    Jack = 11,
    Queen = 12,
    King = 13,
    Ace = 14
};

struct Card {
    Suit suit;
    Rank rank;
};

enum class GameResult {
    PlayerWon,
    DealerWon,
    IsTie
};

class Deck {
private:
    std::vector<Card> deck; // Заменяем std::array на std::vector
public:
    Deck() {
        for (int suit = static_cast<int>(Suit::Clubs); suit <= static_cast<int>(Suit::Spades); suit++) {
            for (int rank = static_cast<int>(Rank::Six); rank <= static_cast<int>(Rank::Ace); rank++) {
                deck.push_back({ static_cast<Suit>(suit), static_cast<Rank>(rank) });
            }
        }
    }

    void shuffle() {
        static std::mt19937 mt{ std::random_device{}() };
        std::shuffle(deck.begin(), deck.end(), mt);
    }

    Card drawCard() {
        // Вытягиваем карту из колоды и возвращаем ее
        Card drawnCard = deck.back();
        deck.pop_back();
        return drawnCard;
    }

    void print() const {
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
};

class Player {
private:
    int playerScore = 0;
    std::vector<Card> hand;
public:
    void drawCard(Deck& deck) {
        Card drawnCard = deck.drawCard();
        hand.push_back(drawnCard);
        playerScore += static_cast<int>(drawnCard.rank);
    }

    int score() const {
        return playerScore;
    }

    bool playerWantsHit()
    {
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

    void resetHand() {
        hand.clear();
        playerScore = 0;
    }
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

class Blackjack : public Casino {
private:
    int maximumScore = 21;
    int minimumDealerScore = 17;

public:
    GameResult play(Deck& deck) override {
        dealer.resetHand();
        player.resetHand();

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

        std::cout << "The dealer is showing: " << dealer.score() << '\n';
        return player.score() > dealer.score() ? GameResult::PlayerWon : GameResult::DealerWon;
    }

    bool isBust() {
        return player.score() > maximumScore || dealer.score() > maximumScore;
    }

     // Возвращает true, если у игрока «перебор». В противном случае - false.
    bool playerTurn(Deck& deck, Player& player) {
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

    bool dealerTurn(Deck& deck, Player& dealer) {
        while (dealer.score() < minimumDealerScore) {
            dealer.drawCard(deck);
        }
        std::cout << "The dealer is showing: " << dealer.score() << '\n';
        return isBust();
    }
};

class Nine : public Casino {
private:
    int maximumScore = 9;
    int minimumDealerScore = 6;

public:
    GameResult play(Deck& deck) override {
        // Реализуйте логику игры в Девятку здесь
    }

    bool isBust()
    {
        return player.score() > maximumScore; 
    }

    // Возвращает true, если у игрока «перебор». В противном случае - false.
    bool playerTurn(Deck& deck, Player& player) {
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

    bool dealerTurn(Deck& deck, Player& dealer)
    {
        while (dealer.score() < minimumDealerScore)
        {
            dealer.drawCard(deck);
        }
        std::cout << "The dealer is showing: " << dealer.score() << '\n';
        return isBust();
    }
};


int main() {
    Deck deck;
    deck.shuffle();
    deck.shuffle();
    Blackjack a; 
    GameResult result = a.play(deck);

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
}


