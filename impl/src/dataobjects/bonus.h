
#ifndef __BONUS_H__
#define __BONUS_H__

#include <string>
#include "utils/datehelper.h"

class Bonus final {

public:

    Bonus();
    ~Bonus();

    Bonus(const Bonus&) = delete;
    Bonus(Bonus&&) = delete;
    Bonus& operator=(const Bonus&) = delete;
    Bonus& operator=(Bonus&&) = delete;

    unsigned int pk_bonus;
    unsigned int fk_investor;
    DateHelper date;
    std::string short_name;
    std::string description;
    std::string comment;
    std::string reward;

private:

};

#endif // __BONUS_H__
