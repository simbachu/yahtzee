#ifndef SCORECARD_H
#define SCORECARD_H

#include <array>
#include <vector>
#include "YahtzeeRules.h"

class ScoreCard{
    private:
    YahtzeeRules& rules;
    std::array<short, 16> scores;
    void bonus_check();
    
    public:
    ScoreCard(YahtzeeRules& r);

    std::vector<short> available_categories();
    
    std::array<short, 15> max_points_from_roll(std::array<short, 5> roll);

    bool is_category_available(short category);

    void score(short points, short category);
};

#endif