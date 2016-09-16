
#include "investor.h"

Investor::Investor():
pk_investor{}, name{}, email{}, description{}, date_of_inclusion{}
{
}

Investor::~Investor(){
}

Investor::Investor(const Investor &other):
pk_investor{other.pk_investor}, name{other.name}, email{other.email},
description{other.description}, date_of_inclusion{other.date_of_inclusion}
{
}
