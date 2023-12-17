#pragma once
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
