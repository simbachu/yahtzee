#ifndef DICEROLLER_H
#define DICEROLLER_H

#include <random>

class DiceRoller{
    private:
    std::mt19937 mt;
    std::uniform_int_distribution<short> d6;
    public:
    DiceRoller();

    short roll();
};

#endif