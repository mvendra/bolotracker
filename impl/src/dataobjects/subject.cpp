
#include "subject.h"

Subject::Subject():
pk_subject{}, tag{}, description{}, date_of_inclusion{}
{
}

Subject::Subject(const Subject &other):
pk_subject{other.pk_subject}, tag{other.tag}, description{other.description}, date_of_inclusion{other.date_of_inclusion}
{
}

Subject::~Subject(){
}

