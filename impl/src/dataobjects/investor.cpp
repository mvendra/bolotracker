
#include "investor.h"

Investor::Investor(const unsigned int _pk_investor, const std::string &_name,
         const std::string &_email, const std::string &_description, const DateHelper &_date_of_inclusion):
pk_investor{_pk_investor}, name{_name}, email{_email}, description{_description}, date_of_inclusion{_date_of_inclusion}
{}

Investor::~Investor(){
}

Investor::Investor(const Investor &other):
pk_investor{other.pk_investor}, name{other.name}, email{other.email},
description{other.description}, date_of_inclusion{other.date_of_inclusion}
{}

Investor::Investor(Investor &&other):
pk_investor{ std::move(other.pk_investor) },
name{ std::move(other.name) },
email{ std::move(other.email) },
description{ std::move(other.description) },
date_of_inclusion{ std::move(other.date_of_inclusion) }
{}
