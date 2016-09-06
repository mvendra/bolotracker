
#ifndef __DATEHELPER_H__
#define __DATEHELPER_H__

#include <string>

class DateHelper {

// textdate, whereever it is present, is in the
// form of "ddmmyyyy", no slash, no space, just 8 ascii numbers

public:

    DateHelper(const std::string &textdate);

    DateHelper(const unsigned short _day,
               const unsigned short _month,
               const unsigned short _year);

    ~DateHelper(){}

    DateHelper(const DateHelper&) = delete;
    DateHelper(DateHelper&&) = delete;
    DateHelper& operator=(const DateHelper&) = delete;
    DateHelper& operator=(DateHelper&&) = delete;

    static bool isValidDate(const std::string &textdate);
    static bool isValidDate(const unsigned short _day,
                     const unsigned short _month,
                     const unsigned short _year);

    bool setDate(const std::string &textdate);
    bool setDate(const unsigned short _day,
                 const unsigned short _month,
                 const unsigned short _year) const;

    std::string getDateString() const;
    void getDateNumbers(unsigned short &_day,
                        unsigned short &_month,
                        unsigned short &_year) const;

private:

    unsigned short day;
    unsigned short month;
    unsigned short year;

};

#endif // __DATEHELPER_H__
