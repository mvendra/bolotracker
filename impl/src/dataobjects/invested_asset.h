
#ifndef __INVESTED_ASSET_H__
#define __INVESTED_ASSET_H__

#include <string>
#include <utils/datehelper.h>

#include "dataobjects/investor.h"
#include "dataobjects/currency.h"

class InvestedAsset final {

public:

    InvestedAsset(const unsigned int _pk_invested_asset, const Investor &_investor, const Currency &_currency,
                  const DateHelper &_date, const std::string &_short_name, const std::string &_description,
                  const std::string &_comment, const double _price);

    InvestedAsset(const InvestedAsset &_other);
    InvestedAsset(InvestedAsset&&);
    ~InvestedAsset();

    InvestedAsset() = delete;
    InvestedAsset& operator=(const InvestedAsset&) = delete;
    InvestedAsset& operator=(InvestedAsset&&) = delete;

    unsigned int pk_invested_asset;
    Investor investor;
    Currency currency;

    DateHelper date;
    std::string short_name;
    std::string description;
    std::string comment;
    double price;

private:

};

#endif // __INVESTED_ASSET_H__
