
#include "invested_asset.h"

InvestedAsset::InvestedAsset(const unsigned int _pk_invested_asset, const Investor &_investor, const Currency &_currency,
              const DateHelper &_date, const std::string &_short_name, const std::string &_description,
              const std::string &_comment, const double _price):
pk_invested_asset{_pk_invested_asset}, investor{_investor}, currency{_currency}, date{_date}, short_name{_short_name},
description{_description}, comment{_comment}, price{_price}
{}

InvestedAsset::InvestedAsset(const InvestedAsset &_other):
pk_invested_asset{_other.pk_invested_asset}, investor{_other.investor}, currency{_other.currency},
date{_other.date}, short_name{_other.short_name}, description{_other.description},
comment{_other.comment}, price{_other.price}
{}

InvestedAsset::~InvestedAsset(){
}
