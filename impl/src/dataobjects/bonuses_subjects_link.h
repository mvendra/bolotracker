
#ifndef __BONUSES_SUBJECTS_LINK_H__
#define __BONUSES_SUBJECTS_LINK_H__

class BonusesSubjectsLink final {

public:

    BonusesSubjectsLink(const unsigned int _fk_bonus, const unsigned int _fk_subject);
    BonusesSubjectsLink(const BonusesSubjectsLink &_other);
    ~BonusesSubjectsLink();

    BonusesSubjectsLink() = delete;
    BonusesSubjectsLink(BonusesSubjectsLink&&) = delete;
    BonusesSubjectsLink& operator=(const BonusesSubjectsLink&) = delete;
    BonusesSubjectsLink& operator=(BonusesSubjectsLink&&) = delete;

    unsigned int fk_bonus;
    unsigned int fk_subject;

private:

};

#endif // __BONUSES_SUBJECTS_LINK_H__

