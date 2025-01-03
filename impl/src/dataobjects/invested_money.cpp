
#include "invested_money.h"

InvestedMoney::InvestedMoney(const unsigned int _pk_invested_money, const Investor &_investor, const Currency &_currency,
              const DateHelper &_date, const std::string &_short_name, const std::string &_description,
              const std::string &_comment, const double _amount):
pk_invested_money{_pk_invested_money}, investor{_investor}, currency{_currency}, date{_date},
short_name{_short_name}, description{_description}, comment{_comment}, amount{_amount}
{}

InvestedMoney::InvestedMoney(const InvestedMoney &_other):
pk_invested_money{_other.pk_invested_money}, investor{_other.investor}, currency{_other.currency},
date{_other.date}, short_name{_other.short_name}, description{_other.description},
comment{_other.comment}, amount{_other.amount}
{}

InvestedMoney::InvestedMoney(InvestedMoney &&_other):
pk_invested_money{ std::move(_other.pk_invested_money) },
investor{ std::move(_other.investor) },
currency{ std::move(_other.currency) },
date{ std::move(_other.date) },
short_name{ std::move(_other.short_name) },
description{ std::move(_other.description) },
comment{ std::move(_other.comment) },
amount{ std::move(_other.amount) }
{}

InvestedMoney::~InvestedMoney(){
}
