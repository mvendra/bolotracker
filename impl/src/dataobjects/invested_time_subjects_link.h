
#ifndef __INVESTED_TIME_SUBJECTS_LINK_H__
#define __INVESTED_TIME_SUBJECTS_LINK_H__

class InvestedTimeSubjectsLink final {

public:

    InvestedTimeSubjectsLink();
    ~InvestedTimeSubjectsLink();

    InvestedTimeSubjectsLink(const InvestedTimeSubjectsLink&) = delete;
    InvestedTimeSubjectsLink(InvestedTimeSubjectsLink&&) = delete;
    InvestedTimeSubjectsLink& operator=(const InvestedTimeSubjectsLink&) = delete;
    InvestedTimeSubjectsLink& operator=(InvestedTimeSubjectsLink&&) = delete;

    unsigned int fk_invested_time;
    unsigned int fk_subject;

private:

};

#endif // __INVESTED_TIME_SUBJECTS_LINK_H__
