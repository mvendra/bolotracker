
#include "invested_money.h"

InvestedMoney::InvestedMoney(const unsigned int _pk_invested_money, const unsigned int _fk_investor, const unsigned int _fk_currency,
              const DateHelper &_date, const std::string &_short_name, const std::string &_description,
              const std::string &_comment, const double _amount):
pk_invested_money{_pk_invested_money}, fk_investor{_fk_investor}, fk_currency{_fk_currency}, date{_date},
short_name{_short_name}, description{_description}, comment{_comment}, amount{_amount}
{}

InvestedMoney::InvestedMoney(const InvestedMoney &_other):
pk_invested_money{_other.pk_invested_money}, fk_investor{_other.fk_investor}, fk_currency{_other.fk_currency},
date{_other.date}, short_name{_other.short_name}, description{_other.description},
comment{_other.comment}, amount{_other.amount}
{}

InvestedMoney::~InvestedMoney(){
}
