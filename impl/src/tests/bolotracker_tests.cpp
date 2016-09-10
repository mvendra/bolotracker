
#include "tests/bolotracker_tests.h"

#include "tests/datehelper_tests.h"
#include "testforecho.h"

void test_accrue(bool &flag_holder, bool func){
    flag_holder &= func;
}

bool test_all(){

    bool result {true};

    test_accrue(result, test_datehelper());

    return result;
}
