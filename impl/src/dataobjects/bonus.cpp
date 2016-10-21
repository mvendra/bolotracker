
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

Bonus::Bonus(Bonus &&_other):
pk_bonus{ std::move(_other.pk_bonus) },
investor{ std::move(_other.investor) },
date{ std::move(_other.date) },
short_name{ std::move(_other.short_name) },
description{ std::move(_other.description) },
comment{ std::move(_other.comment) },
reward{ std::move(_other.reward) }
{}

Bonus::~Bonus(){
}
