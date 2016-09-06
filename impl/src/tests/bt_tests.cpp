
#include "tests/bt_tests.h"

#include "utils/datehelper.h"

#include <iostream>

bool test_all(){
    bool acc = true;
    acc &= test_datehelper();
    return acc;
}

bool test_datehelper(){

    // test date validator
    bool total = true;
    bool each = true;

    // date should be valid
    each = DateHelper::isValidDate(22, 06, 1997);
    if (!each){
        std::cout << "Date should be valid." << std::endl;
        total = false;
    }

    // date should be invalid
    each = DateHelper::isValidDate(32, 06, 1997);
    if (each){
        std::cout << "Date should be invalid." << std::endl;
        total = false;
    }

    each = DateHelper::isValidDate("05/08/2001");
    if (!each){
        std::cout << "Date should be valid." << std::endl;
        total = false;
    }

    each = DateHelper::isValidDate("05/13/1985");
    if (each){
        std::cout << "Date should be invalid." << std::endl;
        total = false;
    }

    return total;

}
