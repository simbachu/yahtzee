#ifndef YAHTZEEPLAYER_H
#define YAHTZEEPLAYER_H

#include <string>
#include <iostream>
#include "YahtzeeRules.h"
#include "DiceRoller.h"
#include "ScoreCard.h"

class Player{
    private:
    YahtzeeRules &rules;
    std::string name;
    ScoreCard tally;
    std::array<short, 5> roll;
    void sort_rolls();
    void roll_all(DiceRoller& dice);
    void roll_one(short d, DiceRoller& dice);
    void print_dice();

    public:
    Player(YahtzeeRules& r, std::string player_name);
    void attempt(DiceRoller& dice);
};

#endif