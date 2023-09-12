#include <algorithm> // std::shuffle
#include <array>
#include <ctime>     // std::time
#include <iostream>
#include <random>    // std::mt19937
#include <vector>    

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
    std::vector<Card> deck;
public:
    // Конструктор, который заполняет колоду картами
    Deck() {
        for (int suit = static_cast<int>(Suit::Clubs); suit <= static_cast<int>(Suit::Spades); suit++) {
            for (int rank = static_cast<int>(Rank::Six); rank <= static_cast<int>(Rank::Ace); rank++) {
                deck.push_back({ static_cast<Suit>(suit), static_cast<Rank>(rank) });
            }
        }
    }

    // Функция для перемешивания колоды
    void shuffle() {
        static std::mt19937 mt{ std::random_device{}() };
        std::shuffle(deck.begin(), deck.end(), mt);
    }

    // Функция для вытягивания карты из колоды и возврата её
    Card drawCard() {
        Card drawnCard = deck.back();
        deck.pop_back();
        return drawnCard;
    }

    // Функция для вывода содержимого колоды (для проверки перемешивания)
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
    // Функция для вытягивания карты игроку
    void drawCard(Deck& deck) {
        Card drawnCard = deck.drawCard();
        hand.push_back(drawnCard);
        playerScore += static_cast<int>(drawnCard.rank);
    }

    // Функция для получения суммы очков игрока
    int score() const {
        return playerScore;
    }

    // Функция для определения, хочет ли игрок взять ещё карту
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

    // Функция для сброса карт из руки игрока и счёта очков
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
    // Виртуальная функция для начала игры (полиморфизм)
    virtual GameResult play(Deck& deck) = 0;

    // Виртуальная функция для хода игрока (полиморфизм)
    virtual bool playerTurn(Deck& deck, Player& player) = 0;

    // Виртуальная функция для проверки перебора
    virtual bool isBust() = 0;

    // Виртуальная функция для хода дилера (полиморфизм)
    virtual bool dealerTurn(Deck& deck, Player& dealer) = 0;
};

class Blackjack : public Casino {
private:
    int maximumScore = 21;
    int minimumDealerScore = 17;

public:
    // Функция для проведения игры в Блэкджек
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

        return player.score() > dealer.score() ? GameResult::PlayerWon : GameResult::DealerWon;
    }

    // Функция для проверки перебора
    bool isBust() {
        return player.score() > maximumScore || dealer.score() > maximumScore;
    }

    // Функция для хода игрока в Блэкджек
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

    // Функция для хода дилера в Блэкджек
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
    // Реализуйте логику игры в Девятку здесь
    GameResult play(Deck& deck) override {
        // Реализация правил игры в Девятку
    }

    // Функция для проверки перебора
    bool isBust()
    {
        return player.score() > maximumScore;
    }

    // Функция для хода игрока в Девятку
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

    // Функция для хода дилера в Девятку
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
    while (true) {
        Deck deck;
        deck.shuffle(); // Перемешиваем существующую колоду перед каждым раундом 
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
