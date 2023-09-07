#include <algorithm> // std::shuffle
#include <array>
#include <ctime>     // std::time
#include <iostream>
#include <random>    // std::mt19937
#include <vector>    // ��������� ��������� ��� std::vector

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

class Deck {
private:
    std::vector<Card> deck; // �������� std::array �� std::vector
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
        // ���������� ����� �� ������ � ���������� ��
        Card drawnCard = deck.back();
        deck.pop_back();
        return drawnCard;
    }

    void print() const {
        for (const Card& card : deck) {
            // ������� ����� � ������� ������ �����
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
    Casino() : deck(), player(), dealer() {//?? ����� ���� �� ���� ������� 
        deck.shuffle();
    }

    virtual bool play(Deck& deck) = 0;
    virtual bool playerTurn(Deck& deck, Player& player) = 0;
    virtual bool isBust() = 0;
    virtual bool dealerTurn(Deck& deck, Player& dealer) = 0;
};

class Blackjack : public Casino {
private:
    int maximumScore = 21;
    int minimumDealerScore = 17;

public:
    bool play(Deck& deck) override
    {
        Player dealer{};
        Player player{};

        dealer.resetHand();
        player.resetHand();

        dealer.drawCard(deck);

        std::cout << "The dealer is showing: " << dealer.score() << '\n';

        player.drawCard(deck);
        player.drawCard(deck);

        if (playerTurn(deck, player))
        {
            return false;
        }

        if (dealerTurn(deck, dealer))
        {
            return true;
        }
        std::cout << "The dealer is showing: " << dealer.score() << '\n';
        return (player.score() > dealer.score());
    }

    bool isBust()
    {
        return player.score() > maximumScore;
    }

    // ���������� true, ���� � ������ ��������. � ��������� ������ - false.
    bool playerTurn(Deck& deck, Player& player)
    {
        while (true)
        {
            std::cout << "You have: " << player.score() << '\n';

            if (isBust())
            {
                return true;
            }
            else
            {
                if (player.playerWantsHit())
                {
                    player.drawCard(deck);
                }
                else
                {
                    // � ������ ��� ��������.
                    return false;
                }
            }
        }
    }

    bool dealerTurn(Deck& deck, Player& dealer)
    {
        while (dealer.score() < minimumDealerScore)
        {
            dealer.drawCard(deck);
        }

        return isBust();
    }
};

class Nine : public Casino {
private:
    int maximumScore = 9;
    int minimumDealerScore = 6;

public:
    bool play(Deck& deck) override {
        // ���������� ������ ���� � ������� �����
    }

    bool isBust()
    {
        return player.score() > maximumScore;
    }

    // ���������� true, ���� � ������ ��������. � ��������� ������ - false.
    bool playerTurn(Deck& deck, Player& player)
    {
        while (true)
        {
            std::cout << "You have: " << player.score() << '\n';

            if (isBust())
            {
                return true;
            }
            else
            {
                if (player.playerWantsHit())
                {
                    player.drawCard(deck);
                }
                else
                {
                    // � ������ ��� ��������.
                    return false;
                }
            }
        }
    }

    bool dealerTurn(Deck& deck, Player& dealer)
    {
        while (dealer.score() < minimumDealerScore)
        {
            dealer.drawCard(deck);
        }

        return isBust();
    }
};


//markkdown: �������� � ��� ��� ���������� ��� � ���� ������ �����!!!
int main() {
    Deck deck;
    deck.shuffle();

    while (true) {
        Blackjack a;

        if (a.play(deck)) {
            std::cout << "You win!\n";
        }
        else {
            std::cout << "You lose!\n";
        }

        std::cout << "Do you want to play another round? (y/n): ";
        char ch;
        std::cin >> ch;

        if (ch != 'y') {
            break; // ���� ����� �� ����� ������ ��� ���, ��������� ����.
        }
    }

    return 0;
}