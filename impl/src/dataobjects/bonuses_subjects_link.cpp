
#include "bonuses_subjects_link.h"

BonusesSubjectsLink::BonusesSubjectsLink(const unsigned int _fk_bonus, const unsigned int _fk_subject):
fk_bonus{_fk_bonus}, fk_subject{_fk_subject}
{}

BonusesSubjectsLink::BonusesSubjectsLink(const BonusesSubjectsLink &_other):
fk_bonus{_other.fk_bonus}, fk_subject{_other.fk_bonus}
{}

BonusesSubjectsLink::~BonusesSubjectsLink(){
}
