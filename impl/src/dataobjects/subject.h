
#ifndef __SUBJECT_H__
#define __SUBJECT_H__

#include <string>
#include "utils/datehelper.h"

class Subject final {

public:

    Subject();
    ~Subject();

    Subject(const Subject&);
    Subject& operator=(const Subject&) = delete;
    Subject(Subject&&) = delete;
    Subject& operator=(Subject&&) = delete;

    unsigned int pk_subject;
    std::string tag;
    std::string description;
    DateHelper date_of_inclusion;

private:

};

#endif // __SUBJECT_H__

