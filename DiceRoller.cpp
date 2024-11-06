#include "DiceRoller.h"

DiceRoller::DiceRoller() : 
                mt{std::random_device{}()}, 
                d6{1, 6} 
                {}

short DiceRoller::roll()  {
        return d6(mt);
    }