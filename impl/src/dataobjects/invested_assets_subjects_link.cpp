
#include "invested_assets_subjects_link.h"

InvestedAssetsSubjectsLink::InvestedAssetsSubjectsLink(const unsigned int _fk_invested_asset, const unsigned int _fk_subject):
fk_invested_asset{_fk_invested_asset}, fk_subject{_fk_subject}
{}

InvestedAssetsSubjectsLink::InvestedAssetsSubjectsLink(const InvestedAssetsSubjectsLink &_other):
fk_invested_asset{_other.fk_invested_asset}, fk_subject{_other.fk_subject}
{}

InvestedAssetsSubjectsLink::~InvestedAssetsSubjectsLink(){
}

