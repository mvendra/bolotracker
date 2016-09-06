
#include "tests/bt_tests.h"

#include "utils/datehelper.h"

#include "exceptions/ex_invalid_date.h"
#include "exceptions/ex_notreached.h"

#include "utils/unit_test.h"

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

    // port all the older tests to unit_test

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
    {
        try {
            DateHelper dh{7, 80, 1978};
            std::cout << "Should raise exception" << std::endl;
        } catch (const Ex_Invalid_Date& ex){
            each = true;
        }
    }
    total &= each;

    // should throw exception when trying to set bad date
    each = false;
    {
        DateHelper dh{7, 5, 1985};
        try {
            dh.setDate("35/20/2000");
            std::cout << "Should raise exception" << std::endl;
        } catch (const Ex_Invalid_Date& ex){
            each = true;
        }
    }
    total &= each;

    // should return the same text date as the one passed during construction
    /*{
        const std::string templ = "03/03/1993";
        DateHelper dh{templ};
        each = (dh.getDateString() == templ);
        if (!each){
            std::cout << "Init date and later fetched date should match" << std::endl;
        }
    }
    total &= each;*/

    //////////////////////////////////////////////////////////

    // should return the same text date as the one passed during construction
    {
        const std::string templ = "03/03/1993";
        DateHelper dh{templ};
        test_eq(total, "Init date and later fetched date should match", templ, dh.getDateString());
    }

    {
        int one = 1;
        int two = 1;
        auto comp = [](auto p1, auto p2) { return (p1 == p2); };
        test(total, "must be same", one, two, comp);
    }

    /////////////////////////////////////////

    // should throw exception when trying to set bad date
    auto p = [](){ 
        DateHelper dh{7, 5, 1985};
        //dh.setDate("35/20/2000");
    };

    //test_ex<Ex_Invalid_Date>(total, "Should raise exception", p);
    test_nex<Ex_Invalid_Date>(total, "Should not raise exception", [](){ DateHelper dh{7, 5, 1985}; });
    test_ex<Ex_Invalid_Date>(total, "Should raise exception", [](){ DateHelper dh{7, 5, 1985}; dh.setDate("35/20/2000"); });

    test_ex<Ex_NotReached>(total, "mvdebug", [](){ DateHelper dh{7, 5, 1985}; dh.setDate("35/20/2000"); });

    /*each = false;
    {
        
        try {
            
            std::cout << "Should raise exception" << std::endl;
        } catch (const Ex_Invalid_Date& ex){
            each = true;
        }
    }
    total &= each;*/

    /////////////////////////////

    //test_nex<Ex_

    return total;

}
