
#ifndef __INVESTED_ASSET_H__
#define __INVESTED_ASSET_H__

#include <string>
#include <utils/datehelper.h>

class InvestedAsset final {

public:

    InvestedAsset(const unsigned int _pk_invested_asset, const unsigned int _fk_investor, const unsigned int _fk_currency,
                  const DateHelper &_date, const std::string &_short_name, const std::string &_description,
                  const std::string &_comment, const double _price);

    InvestedAsset(const InvestedAsset &_other);
    ~InvestedAsset();

    InvestedAsset() = delete;
    InvestedAsset(InvestedAsset&&) = delete;
    InvestedAsset& operator=(const InvestedAsset&) = delete;
    InvestedAsset& operator=(InvestedAsset&&) = delete;

    unsigned int pk_invested_asset;
    unsigned int fk_investor;
    unsigned int fk_currency;

    DateHelper date;
    std::string short_name;
    std::string description;
    std::string comment;
    double price;

private:

};

#endif // __INVESTED_ASSET_H__
