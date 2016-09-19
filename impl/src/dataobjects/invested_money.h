
#ifndef __INVESTED_MONEY_H__
#define __INVESTED_MONEY_H__

#include <string>
#include "utils/datehelper.h"

#include "dataobjects/investor.h"
#include "dataobjects/currency.h"

class InvestedMoney final {

public:

    InvestedMoney(const unsigned int _pk_invested_money, const Investor &_investor, const Currency &_currency,
                  const DateHelper &_date, const std::string &_short_name, const std::string &_description,
                  const std::string &_comment, const double _amount);

    InvestedMoney(const InvestedMoney&);
    ~InvestedMoney();

    InvestedMoney() = delete;
    InvestedMoney(InvestedMoney&&) = delete;
    InvestedMoney& operator=(const InvestedMoney&) = delete;
    InvestedMoney& operator=(InvestedMoney&&) = delete;

    unsigned int pk_invested_money;
    Investor investor;
    Currency currency;

    DateHelper date;
    std::string short_name;
    std::string description;
    std::string comment;
    double amount;

private:

};

#endif // __INVESTED_MONEY_H__
