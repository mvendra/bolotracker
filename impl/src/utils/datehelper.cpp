
#include "utils/datehelper.h"
#include "utils/utils.h"

#include "exceptions/ex_invalid_date.h"

DateHelper::DateHelper(const unsigned short _day,
                       const unsigned short _month,
                       const unsigned short _year):
day{_day}, month{_month}, year{_year}{

    if (!isValidDate(_day, _month, _year)){
        EX_THROW(Ex_Invalid_Date, "Invalid date: " + convertFromNumbers(_day, _month, _year));
    }

}

DateHelper::DateHelper(const std::string &textdate):day{0}, month{0}, year{0}{
    if (!isValidDate(textdate)){
        EX_THROW(Ex_Invalid_Date, "Invalid date: " + textdate);
    }
}

bool DateHelper::isValidDate(const std::string &textdate) {

    tm aux;
    return strptime(textdate.c_str(), "%d/%m/%Y", &aux);

}

bool DateHelper::isValidDate(const unsigned short _day,
                 const unsigned short _month,
                 const unsigned short _year) {

    std::string txtdate = convertFromNumbers(_day, _month, _year);
    tm aux;
    return strptime(txtdate.c_str(), "%d/%m/%Y", &aux);

}

void DateHelper::convertFromText(const std::string &textdate,
                                 unsigned short &_day,
                                 unsigned short &_month,
                                 unsigned short &_year)
{

    if (textdate.size() < 10){
        _day = 0;
        _month = 0;
        _year = 0;
        return; // no cake.
    }

    std::string strday;
    std::string strmonth;
    std::string stryear;

    strday = textdate.substr(0, 2);
    strmonth = textdate.substr(3, 2);
    stryear = textdate.substr(6, 4);

    _day = strToUshort(strday);
    _month = strToUshort(strmonth);
    _year = strToUshort(stryear);

}

std::string DateHelper::convertFromNumbers(const unsigned short _day,
                                           const unsigned short _month,
                                           const unsigned short _year)
{

    char chdate[10]{0};
    sprintf(chdate, "%02d/%02d/%04d", _day, _month, _year);
    std::string ret = chdate;
    return ret;

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
