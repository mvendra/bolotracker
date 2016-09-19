
#include "invested_time.h"

InvestedTime::InvestedTime(const unsigned int _pk_invested_time, const Investor &_investor, const Currency &_currency,
             const DateHelper &_date, const std::string &_description, const std::string &_comment,
             const unsigned int _minutes, const double &_price_per_unit):
pk_invested_time{_pk_invested_time}, investor{_investor}, currency{_currency},
date{_date}, description{_description}, comment{_comment},
minutes{_minutes}, price_per_unit{_price_per_unit}
{}

InvestedTime::InvestedTime(const InvestedTime &_other):
pk_invested_time{_other.pk_invested_time}, investor{_other.investor}, currency{_other.currency},
date{_other.date}, description{_other.description}, comment{_other.comment},
minutes{_other.minutes}, price_per_unit{_other.price_per_unit}
{}

InvestedTime::~InvestedTime(){
}

