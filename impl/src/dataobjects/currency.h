
#ifndef __CURRENCY_H__
#define __CURRENCY_H__

#include <string>
#include "utils/datehelper.h"

class Currency final {

public:

    Currency(const unsigned int _pk_currency, const std::string &_label, const std::string &_description, const DateHelper &_date_of_inclusion);
    Currency(const Currency&);
    Currency(Currency&&);

    ~Currency();

    Currency() = delete;    
    Currency& operator=(const Currency&) = delete;
    Currency& operator=(Currency&&) = delete;

    unsigned int pk_currency;
    std::string label;
    std::string description;
    DateHelper date_of_inclusion;

private:

};

#endif // __CURRENCY_H__

