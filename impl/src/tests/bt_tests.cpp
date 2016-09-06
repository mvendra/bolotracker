
#include "tests/bt_tests.h"

#include "utils/datehelper.h"

#include "exceptions/ex_invalid_date.h"

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
    each = DateHelper::isValidDate(22, 6, 1997);
    if (!each){
        std::cout << "Date should be valid." << std::endl;
        total = false;
    }

    // date should be invalid
    each = DateHelper::isValidDate(32, 6, 1997);
    if (each){
        std::cout << "Date should be invalid." << std::endl;
        total = false;
    }

    // date should be valid
    each = DateHelper::isValidDate("05/08/2001");
    if (!each){
        std::cout << "Date should be valid." << std::endl;
        total = false;
    }

    // date should be invalid
    each = DateHelper::isValidDate("05/13/1985");
    if (each){
        std::cout << "Date should be invalid." << std::endl;
        total = false;
    }

    // conversion from number to text should succeed
    const std::string templ = "06/03/2002";
    std::string r = DateHelper::convertFromNumbers(6, 3, 2002);
    each = (r == templ);
    if (!each){
        std::cout << "Conversion failed." << std::endl;
        total = false;
    }

    // conversion from text to number should succeed
    unsigned short d{0}, m{0}, y{0};
    DateHelper::convertFromText("07/02/2003", d, m, y);
    each = (d == 7) && (m == 2) && (y == 2003);
    if (!each){
        std::cout << "Conversion failed." << std::endl;
        total = false;
    }

    // conversion from text to number should fail
    d = 3; m = 4; y = 2005;
    DateHelper::convertFromText("nope", d, m, y);
    each = (d == 3) && (m == 4) && (y == 2005);
    if (each){
        std::cout << "Conversion should fail." << std::endl;
        total = false;
    }

    // should throw exacly that type of exception
    each = false;
    try {
        DateHelper dh{7, 80, 1978};
        std::cout << "Should raise exception" << std::endl;
    } catch (const Ex_Invalid_Date& ex){
        each = true;
    }
    total &= each;

    return total;

}
