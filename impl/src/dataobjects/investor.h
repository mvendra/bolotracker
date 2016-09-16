
#ifndef __INVESTOR_H__
#define __INVESTOR_H__

#include <string>
#include "utils/datehelper.h"

class Investor final {

public:

    Investor();
    ~Investor();

    Investor(const Investor&);
    Investor(Investor&&) = delete;
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

