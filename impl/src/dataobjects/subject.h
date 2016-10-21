
#ifndef __SUBJECT_H__
#define __SUBJECT_H__

#include <string>
#include "utils/datehelper.h"

class Subject final {

public:

    Subject(const unsigned int _pk_subject, const std::string &_tag,
            const std::string &_description, const DateHelper &_date_of_inclusion);

    Subject(const Subject&);
	Subject(Subject&&);

    ~Subject();

    Subject() = delete;
    Subject& operator=(const Subject&) = delete;
    Subject& operator=(Subject&&) = delete;

    unsigned int pk_subject;
    std::string tag;
    std::string description;
    DateHelper date_of_inclusion;

private:

};

#endif // __SUBJECT_H__

