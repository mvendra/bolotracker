
#include "utils/datehelper.h"

DateHelper::DateHelper(const unsigned short _day,
                       const unsigned short _month,
                       const unsigned short _year):
day{_day}, month{_month}, year{_year}{

    // mvtodo: validate and ...

}

DateHelper::DateHelper(const std::string &textdate):day{0}, month{0}, year{0}{
    // mvtodo: ...
    (void)textdate; // mvdebug: compile plis
}

bool DateHelper::isValidDate(const std::string &textdate) {
    // mvtodo: finish this
    (void)textdate; // mvdebug: compile plis
    return false; // mvdebug
}

bool DateHelper::isValidDate(const unsigned short _day,
                 const unsigned short _month,
                 const unsigned short _year) {
    // mvtodo: finish this
    (void)_day; // mvdebug
    (void)_month; // mvdebug
    (void)_year; // mvdebug
    return false; // mvdebug
}

bool DateHelper::setDate(const std::string &textdate){
    // mvtodo: finish this
    (void)textdate; // mvdebug
    return false; // mvdebug
}

bool DateHelper::setDate(const unsigned short _day,
             const unsigned short _month,
             const unsigned short _year) const {
    // mvtodo: finish this
    (void)_day; // mvdebug
    (void)_month; // mvdebug
    (void)_year; // mvdebug
    return false; // mvdebug
}

std::string DateHelper::getDateString() const {
    // mvtodo: finish this
    return "mvdebug";
}

void DateHelper::getDateNumbers(unsigned short &_day,
                    unsigned short &_month,
                    unsigned short &_year) const {
    // mvtodo: finish this
    _day = 0; // mvdebug
    _month = 0; // mvdebug
    _year = 0; // mvdebug
}
