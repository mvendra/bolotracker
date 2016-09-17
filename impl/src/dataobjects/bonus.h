
#ifndef __BONUS_H__
#define __BONUS_H__

#include <string>
#include "utils/datehelper.h"

class Bonus final {

public:

    Bonus(const unsigned int _pk_bonus, const unsigned int _fk_investor, const DateHelper &_date, const std::string &_short_name,
          const std::string &_description, const std::string &_comment, const std::string &_reward);
    Bonus(const Bonus&);
    ~Bonus();

    Bonus() = delete;
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
