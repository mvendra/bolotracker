
#ifndef __INVESTED_ASSETS_SUBJECTS_LINK_H__
#define __INVESTED_ASSETS_SUBJECTS_LINK_H__

class InvestedAssetsSubjectsLink final {

public:

    InvestedAssetsSubjectsLink(const unsigned int _fk_invested_asset, const unsigned int _fk_subject);
    InvestedAssetsSubjectsLink(const InvestedAssetsSubjectsLink&);
    ~InvestedAssetsSubjectsLink();

    InvestedAssetsSubjectsLink() = delete;
    InvestedAssetsSubjectsLink(InvestedAssetsSubjectsLink&&) = delete;
    InvestedAssetsSubjectsLink& operator=(const InvestedAssetsSubjectsLink&) = delete;
    InvestedAssetsSubjectsLink& operator=(InvestedAssetsSubjectsLink&&) = delete;

    unsigned int fk_invested_asset;
    unsigned int fk_subject;

private:

};

#endif // __INVESTED_ASSETS_SUBJECTS_LINK_H__

