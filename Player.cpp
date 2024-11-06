#include <string>
#include "Player.h"


Player::Player(YahtzeeRules& r, std::string player_name) : 
    rules(r), name(player_name), tally(rules){

    roll.fill(1);
}

void Player::sort_rolls(){
    std::sort(roll.rbegin(), roll.rend());
};

void Player::roll_all(DiceRoller& dice){
    for ( auto it = roll.begin(); it != roll.end(); ++it ){
        *it = dice.roll();
    }
    sort_rolls();
};

void Player::roll_one(short d, DiceRoller& dice){
    roll.at(d) = dice.roll();
};

void Player::print_dice(){
    for ( short r : roll ){
        std::cout << " " << r;
    }
};

void Player::attempt(DiceRoller& dice){
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
                std::cout << i << ": " << rules.categories.at(i) << " (" << potential.at(i) << " points)" << std::endl;
                }
        }
        std::cin >> choice;
        choice -= '0';
    }
    tally.score(potential.at(choice), choice);

    std::cout << name << " scored " << rules.categories.at(choice) << " for " << potential.at(choice) << " points." << std::endl ;

}