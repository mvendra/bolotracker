
#include "currency.h"

Currency::Currency(const unsigned int _pk_currency, const std::string &_label, const std::string &_description, const DateHelper &_date_of_inclusion):
pk_currency{_pk_currency}, label{_label}, description{_description}, date_of_inclusion{_date_of_inclusion}
{}

Currency::Currency(const Currency &other):
pk_currency{other.pk_currency}, label{other.label}, description{other.description}, date_of_inclusion{other.date_of_inclusion}
{}

Currency::~Currency(){}
