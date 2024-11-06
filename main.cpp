#include <iostream>
#include <iterator>
#include <random>
#include <string>
#include <chrono>
#include <array>
#include <utility>
#include <algorithm>
#include "YahtzeeRules.h"
#include "DiceRoller.h"
#include "ScoreCard.h"
#include "Player.h"


int main(){
    YahtzeeRules game;
    std::array<Player, 2> players = {Player(game, "YouMe"), Player(game, "MeYou")};
    DiceRoller dice;
    for ( int i = 1; i <= 15; i++) {
        std::cout << "Turn " << i << std::endl;
        for ( Player active_player : players ){
            active_player.attempt(dice);
        }
    }
}