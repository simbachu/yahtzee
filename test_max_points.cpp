#include <array>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <iterator>

template <class T, std::size_t N>
std::ostream& operator<<(std::ostream& o, const std::array<T, N>& arr)
{
    std::copy(arr.cbegin(), arr.cend(), std::ostream_iterator<T>(o, " "));
    return o;
}

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

std::array<short, 15> max_points_from_roll(std::array<short, 5> roll){
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
};

int main(){
    std::vector<std::array<short, 5>> tests = {
        {1,2,3,4,5},
        {2,2,3,3,3},
        {2,3,3,3,3},
        {3,3,3,3,3},
        {5,3,4,1,2},
        {1,1,2,3,5},
        {5,4,3,2,3},
        {6,5,4,3,2},
        {6,2,3,6,3},
        {1,2,3,3,6},
    };

    std::vector<std::array<short, 15>> results;

    for ( auto t : tests ){
        results.push_back(max_points_from_roll(t));
        for ( int i = 1; i < 15; i++ ){
            if ( results.back().at(i) > 0 ){
                std::cout << categories.at(i) << ": " << results.back().at(i) << std::endl;
            }
        }
        auto result = std::max_element(results.back().begin(), results.back().end());
        std::cout << "The highest score for " << t << "is " << categories.at(std::distance(results.back().begin(), result)) << " with " << *result << std::endl << std::endl;
    }

}