
#ifndef __CURRENCY_H__
#define __CURRENCY_H__

#include <string>
#include "utils/datehelper.h"

class Currency final {

public:

    Currency();
    ~Currency();

    Currency(const Currency&);
    Currency(Currency&&) = delete;
    Currency& operator=(const Currency&) = delete;
    Currency& operator=(Currency&&) = delete;

    unsigned int pk_currency;
    std::string label;
    std::string description;
    DateHelper date_of_inclusion;

private:

};

#endif // __CURRENCY_H__

