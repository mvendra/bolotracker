
#ifndef __INVESTED_TIME_H__
#define __INVESTED_TIME_H__

#include <string>
#include <utils/datehelper.h>

class InvestedTime final {

public:

    InvestedTime();
    ~InvestedTime();

    InvestedTime(const InvestedTime&) = delete;
    InvestedTime(InvestedTime&&) = delete;
    InvestedTime& operator=(const InvestedTime&) = delete;
    InvestedTime& operator=(InvestedTime&&) = delete;

    unsigned int pk_invested_time;
    unsigned int fk_investor;
    unsigned int fk_currency;

    DateHelper date;
    std::string description;
    std::string comment;
    unsigned int minutes;
    double price_per_unit;

private:

};

#endif // __INVESTED_TIME_H__

