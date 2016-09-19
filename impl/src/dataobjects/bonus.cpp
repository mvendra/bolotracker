
#include "bonus.h"

Bonus::Bonus(const unsigned int _pk_bonus, const Investor &_investor, const DateHelper &_date, const std::string &_short_name,
      const std::string &_description, const std::string &_comment, const std::string &_reward):
pk_bonus{_pk_bonus}, investor{_investor}, date{_date}, short_name{_short_name},
description{_description}, comment{_comment}, reward{_reward}
{}

Bonus::Bonus(const Bonus &_other):
pk_bonus{_other.pk_bonus}, investor{_other.investor}, date{_other.date}, short_name{_other.short_name},
description{_other.description}, comment{_other.comment}, reward{_other.reward}
{}

Bonus::~Bonus(){
}
