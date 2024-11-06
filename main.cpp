#include <iostream>
#include <iterator>
#include <random>
#include <string>
#include <chrono>
#include <array>
#include <utility>
#include <algorithm>

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

class DiceRoller{
    private:
    std::mt19937 mt;
    std::uniform_int_distribution<short> d6;
    public:
    DiceRoller() : 
                mt{std::random_device{}()}, 
                d6{1, 6} {
    }

     short roll() {
        return d6(mt);
    }
};

class ScoreCard{
    private:
    std::array<short, 16> scores;
    void bonus_check(){
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
    };
    
    public:
    ScoreCard(){
        scores.fill(-1);
        };

    std::vector<short> available_categories(){
        std::vector<short> r;
        for (short i = 0; i < scores.size(); i++ ){
            if (scores.at(i) == -1){
                r.emplace_back(i);
            }
        }
        return r;
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

    bool is_category_available(short category){
        if(category >= 0 && category < 15){
            return scores.at(category) < 0;
        } else {
            return false;
        }
    };
    void score(short points, short category){
        scores.at(category) = points;   
    }
};

class Player{
    private:
    std::string name;
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
    ScoreCard tally;
    std::array<short, 5> roll = {1};
    void sort_rolls(){
        std::sort(roll.rbegin(), roll.rend());
    };
    void roll_all(DiceRoller& dice){
        for ( auto it = roll.begin(); it != roll.end(); ++it ){
            *it = dice.roll();
        }
        sort_rolls();
    };
    void roll_one(short d, DiceRoller& dice){
        roll.at(d) = dice.roll();
    };
    void print_dice(){
        for ( short r : roll ){
            std::cout << " " << r;
        }
    };

    public:
    Player(std::string player_name){
        name = player_name;
    };
    void attempt(DiceRoller& dice){
        std::string input = "";

        std::cout << "Player " << name << "'s turn to roll." << std::endl;
        
        roll_all(dice);

        std::cout << std::endl << "The initial rolls are";
        print_dice();
        std::cout << ". " << std::endl << "Enter the dice you want to reroll or ENTER to continue.";

        std::cin >> input;
        for ( char c : input ){
            if(c >= '1' && c <= '5'){
                short d = c - '0' - 1;
                roll_one(d, dice);
            }
        }
        sort_rolls();


        std::cout << std::endl << "The current rolls are";
        print_dice();
        std::cout << ". " << std::endl << "Last chance. Enter the dice you want to reroll or ENTER to continue.";
        std::cin >> input;
        for ( char c : input ){
            if(c >= '1' && c <= '5'){
                short d = c - '0' - 1;
                roll_one(d, dice);
            }
        }

        std::cout << std::endl << "The final rolls are";
        print_dice();
        std::array<short, 15> potential = tally.max_points_from_roll(roll);

        char choice = -1;
        while(!tally.is_category_available(choice)){
            std::cout << "Select a category to score against: " << std::endl;
            for (int i = 0; i < 15; i++ ){
                if(tally.is_category_available(i)){
                    std::cout << i << ": " << categories.at(i) << " (" << potential.at(i) << " points)" << std::endl;
                    }
            }
            std::cin >> choice;
            choice -= '0';
        }
        tally.score(potential.at(choice), choice);

        std::cout << name << " scored " << categories.at(choice) << " for " << potential.at(choice) << " points." << std::endl ;

    }
};

int main(){
    std::array<Player, 2> players = {Player("YouMe"), Player("MeYou")};
    DiceRoller dice;
    for ( int i = 1; i <= 15; i++) {
        std::cout << "Turn " << i << std::endl;
        for ( Player active_player : players ){
            active_player.attempt(dice);
        }
    }
}