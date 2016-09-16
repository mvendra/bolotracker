
#include "invested_asset.h"

InvestedAsset::InvestedAsset():
pk_invested_asset{}, fk_investor{}, fk_currency{}, date{}, short_name{},
description{}, comment{}, price{}
{
}

InvestedAsset::~InvestedAsset(){
}
