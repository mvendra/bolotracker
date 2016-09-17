
#include "invested_time_subjects_link.h"

InvestedTimeSubjectsLink::InvestedTimeSubjectsLink(const unsigned int _fk_invested_time, const unsigned int _fk_subject):
fk_invested_time{_fk_invested_time}, fk_subject{_fk_subject}
{}

InvestedTimeSubjectsLink::InvestedTimeSubjectsLink(const InvestedTimeSubjectsLink &_other):
fk_invested_time{_other.fk_invested_time}, fk_subject{_other.fk_subject}
{}

InvestedTimeSubjectsLink::~InvestedTimeSubjectsLink(){
}

