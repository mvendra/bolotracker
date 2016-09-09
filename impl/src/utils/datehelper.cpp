
#include "utils/datehelper.h"
#include "utils/conversions.h"

#include "exceptions/ex_invalid_date.h"

#ifdef __linux__
#include <time.h>
#include <sys/time.h>
#elif _WIN32
#include <windows.h>
#endif

DateHelper::DateHelper():day{0}, month{0}, year{0}{

#ifdef __linux__

    struct timeval tv;
    struct timezone tz;
    struct tm *tm;

    gettimeofday(&tv, &tz);
    tm = localtime(&tv.tv_sec);

    /*sysTime.m_seconds = tm->tm_sec;
    sysTime.m_minutes = tm->tm_min;
    sysTime.m_hours = tm->tm_hour;
    sysTime.m_monthday = tm->tm_mday;
    sysTime.m_month = tm->tm_mon+1;
    sysTime.m_year = tm->tm_year%100;*/

    this->day = tm->tm_mday;
    this->month = tm->tm_mon+1;
    this->year = tm->tm_year + 1900;

#elif _WIN32
    SYSTEMTIME stSysTime;
    GetLocalTime(&stSysTime);

    /*sysTime.m_seconds = stSysTime.wSecond;
    sysTime.m_minutes = stSysTime.wMinute;
    sysTime.m_hours = stSysTime.wHour;
    sysTime.m_monthday = stSysTime.wDay;
    sysTime.m_month = stSysTime.wMonth;
    sysTime.m_year = stSysTime.wYear%100;*/

    this->day = stSysTime.wDay;
    this->month = stSysTime.wMonth;
    this->year = stSysTime.wYear + 1900;

#else
    EX_THROW(Ex_Unsupported_Platform, "Present-date probing not implemented on this platform")
#endif

}

DateHelper::DateHelper(const unsigned short _day,
                       const unsigned short _month,
                       const unsigned short _year):
day{0}, month{0}, year{0}
{
    setDate(_day, _month, _year);
}

DateHelper::DateHelper(const std::string &textdate):
day{0}, month{0}, year{0}
{
    setDate(textdate);
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

    char chdate[11]{0};
    sprintf(chdate, "%02d/%02d/%04d", _day, _month, _year);
    std::string ret {chdate};
    return ret;

}

void DateHelper::setDate(const std::string &textdate){

    if (!isValidDate(textdate)){
        EX_THROW(Ex_Invalid_Date, "Invalid date: " + textdate);
    }

    unsigned short _d{0}, _m{0}, _y{0};
    convertFromText(textdate, _d, _m, _y);

    this->day = _d;
    this->month = _m;
    this->year = _y;

}

void DateHelper::setDate(const unsigned short _day,
             const unsigned short _month,
             const unsigned short _year) {

    if (!isValidDate(_day, _month, _year)){
        EX_THROW(Ex_Invalid_Date, "Invalid date: " + convertFromNumbers(_day, _month, _year));
    }

    this->day = _day;
    this->month = _month;
    this->year = _year;

}

std::string DateHelper::getDateString() const {
    return convertFromNumbers(day, month, year);
}

void DateHelper::getDateNumbers(unsigned short &_day,
                    unsigned short &_month,
                    unsigned short &_year) const {
    _day = day;
    _month = month;
    _year = year;
}
