
#include "invested_money.h"

InvestedMoney::InvestedMoney():
pk_invested_money{}, fk_investor{}, fk_currency{}, date{}, short_name{},
description{}, comment{}, amount{}
{
}

InvestedMoney::~InvestedMoney(){
}
