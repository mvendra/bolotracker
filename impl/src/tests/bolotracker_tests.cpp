
#include "tests/bolotracker_tests.h"

#include "tests/datehelper_tests.h"
#include "tests/database_tests.h"
#include "tests/model_tests.h"

void test_accrue(unsigned int &counter, unsigned int func){
    counter += func;
}

unsigned int test_all(){

    unsigned int result {0};

    test_accrue(result, test_datehelper());
    test_accrue(result, test_database());
    test_accrue(result, test_model());

    return result;
}
