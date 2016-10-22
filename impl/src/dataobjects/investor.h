
#ifndef __INVESTOR_H__
#define __INVESTOR_H__

#include <string>
#include "utils/datehelper.h"

class Investor final {

public:

    Investor(const unsigned int _pk_investor, const std::string &_name,
             const std::string &_email, const std::string &_description, const DateHelper &_date_of_inclusion);

    Investor(const Investor&);
    Investor(Investor&&);
    ~Investor();

    Investor() = delete;
    Investor& operator=(const Investor&) = delete;
    Investor& operator=(Investor&&) = delete;

    unsigned int pk_investor;
    std::string name;
    std::string email;
    std::string description;
    DateHelper date_of_inclusion;

private:

};

#endif // __INVESTOR_H__

