
#ifndef __INVESTED_TIME_H__
#define __INVESTED_TIME_H__

#include <string>
#include <utils/datehelper.h>

#include "dataobjects/investor.h"
#include "dataobjects/currency.h"

class InvestedTime final {

public:

    InvestedTime(const unsigned int _pk_invested_time, const Investor &_investor, const Currency &_currency,
                 const DateHelper &_date, const std::string &_description, const std::string &_comment,
                 const unsigned int _minutes, const double &_price_per_unit);

    InvestedTime(const InvestedTime&);
    InvestedTime(InvestedTime&&);
    ~InvestedTime();

    InvestedTime() = delete;
    InvestedTime& operator=(const InvestedTime&) = delete;
    InvestedTime& operator=(InvestedTime&&) = delete;

    unsigned int pk_invested_time;
    Investor investor;
    Currency currency;

    DateHelper date;
    std::string description;
    std::string comment;
    unsigned int minutes;
    double price_per_unit;

private:

};

#endif // __INVESTED_TIME_H__

