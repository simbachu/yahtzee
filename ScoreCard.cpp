#include <vector>
#include <string>
#include <array>
#include "ScoreCard.h"

ScoreCard::ScoreCard(YahtzeeRules& r) : rules(r) {
    scores.fill(-1);
};

void ScoreCard::bonus_check(){
    if (scores.at(ONES) 
    + scores.at(TWOS) 
    + scores.at(THREES) 
    + scores.at(FOURS) 
    + scores.at(FIVES) 
    + scores.at(SIXES) > 62){
        if (scores.at(BONUS) < 0){
            scores.at(BONUS) = 50;
        }
    }
}

std::vector<short> ScoreCard::available_categories(){
    std::vector<short> r;
    for (short i = 0; i < scores.size(); i++ ){
        if (scores.at(i) == -1){
            r.emplace_back(i);
        }
    }
    return r;
}

std::array<short, 15> ScoreCard::max_points_from_roll(std::array<short, 5> roll){
    std::array<short, 15> points = { 0 };
    short sum = 0;
    short ladder_acc = 0;
    std::pair<short, short> house;
    std::array<short, 7> num_val = {0};

    for( short r : roll ){
            num_val.at(r) += 1;
            points.at(r) += r;
            sum += r;
        }
    points.at(CHANCE) = sum;

    for (short i = 1; i < 6; i++){

        switch (num_val.at(i)){
            case 5:
            points.at(YAHTZEE) = 50;
            case 4: 
            points.at(QUADRUPLE) = 4 * i;
            case 3:
            points.at(TRIPLE) = 3 * i;
            house.first = i;
            case 2:
            if (points.at(PAIR) > 0){
                points.at(TWO_PAIRS) = points.at(PAIR) + 2 * i;
            }
            points.at(PAIR) = 2 * i;
            if(house.first!=i){
                house.second = i;
            }
            break;
            case 1: 
            ladder_acc++;
            break;
        }

        if(house.first > 0 && house.second > 0){
            points.at(FULL_HOUSE) = sum;
        }

        if (ladder_acc == 5){
            switch (sum){ 
                case 15:
                    points.at(SM_LADDER) = sum;
                    break;
                case 20:
                    points.at(BIG_LADDER) = sum;
                    break;
            }

        }
    }
    return points;
}

bool ScoreCard::is_category_available(short category){
    if(category >= 0 && category < 15){
        return scores.at(category) < 0;
    } else {
        return false;
    }
}

