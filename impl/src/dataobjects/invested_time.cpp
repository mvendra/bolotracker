
#include "invested_time.h"

InvestedTime::InvestedTime(const unsigned int _pk_invested_time, const unsigned int _fk_investor, const unsigned int _fk_currency,
             const DateHelper &_date, const std::string &_description, const std::string &_comment,
             const unsigned int _minutes, const double &_price_per_unit):
pk_invested_time{_pk_invested_time}, fk_investor{_fk_investor}, fk_currency{_fk_currency},
date{_date}, description{_description}, comment{_comment},
minutes{_minutes}, price_per_unit{_price_per_unit}
{}

InvestedTime::InvestedTime(const InvestedTime &_other):
pk_invested_time{_other.pk_invested_time}, fk_investor{_other.fk_investor}, fk_currency{_other.fk_currency},
date{_other.date}, description{_other.description}, comment{_other.comment},
minutes{_other.minutes}, price_per_unit{_other.price_per_unit}
{}

InvestedTime::~InvestedTime(){
}

