
#include "tests/bolotracker_tests.h"

#include "tests/datehelper_tests.h"
#include "tests/database_tests.h"
#include "tests/model_tests.h"

void test_accrue(bool &flag_holder, bool func){
    flag_holder &= func;
}

bool test_all(){

    bool result {true};

    test_accrue(result, test_datehelper());
    test_accrue(result, test_database());
    test_accrue(result, test_model());

    return result;
}
