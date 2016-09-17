
#include "invested_asset.h"

InvestedAsset::InvestedAsset(const unsigned int _pk_invested_asset, const unsigned int _fk_investor, const unsigned int _fk_currency,
              const DateHelper &_date, const std::string &_short_name, const std::string &_description,
              const std::string &_comment, const double _price):
pk_invested_asset{_pk_invested_asset}, fk_investor{_fk_investor}, fk_currency{_fk_currency}, date{_date}, short_name{_short_name},
description{_description}, comment{_comment}, price{_price}
{}

InvestedAsset::InvestedAsset(const InvestedAsset &_other):
pk_invested_asset{_other.pk_invested_asset}, fk_investor{_other.fk_investor}, fk_currency{_other.fk_currency},
date{_other.date}, short_name{_other.short_name}, description{_other.description},
comment{_other.comment}, price{_other.price}
{}

InvestedAsset::~InvestedAsset(){
}
