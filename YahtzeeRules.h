#ifndef YAHTZEERULES_H
#define YAHTZEERULES_H

#include <array>
#include <string>

enum Categories{
    CHANCE,
    ONES,
    TWOS,
    THREES,
    FOURS,
    FIVES,
    SIXES,
    PAIR,
    TWO_PAIRS,
    TRIPLE,
    QUADRUPLE,
    SM_LADDER,
    BIG_LADDER,
    FULL_HOUSE,
    YAHTZEE,
    BONUS
};

class YahtzeeRules
{
private:

public:
    std::array<std::string, 15> categories = {
    "Chance",
    "Ones",
    "Twos",
    "Threes",
    "Fours",
    "Fives",
    "Sixes",
    "Pair",
    "Two pairs",
    "Triple",
    "Quadruple",
    "Small ladder",
    "Big ladder",
    "Full house",
    "YAHTZEE"
    };
};

#endif