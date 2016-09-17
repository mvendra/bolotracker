
#include "subject.h"

Subject::Subject(const unsigned int _pk_subject, const std::string &_tag,
        const std::string &_description, const DateHelper &_date_of_inclusion):
pk_subject{_pk_subject}, tag{_tag}, description{_description}, date_of_inclusion{_date_of_inclusion}
{}

Subject::Subject(const Subject &other):
pk_subject{other.pk_subject}, tag{other.tag}, description{other.description}, date_of_inclusion{other.date_of_inclusion}
{}

Subject::~Subject(){}

