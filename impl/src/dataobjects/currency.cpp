
#include "currency.h"

Currency::Currency():
pk_currency{}, label{}, description{}, date_of_inclusion{}
{
}

Currency::Currency(const Currency &other):
pk_currency{other.pk_currency}, label{other.label}, description{other.description}, date_of_inclusion{other.date_of_inclusion}
{
}

Currency::~Currency(){
}

