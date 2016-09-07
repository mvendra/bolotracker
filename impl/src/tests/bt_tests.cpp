
#include "tests/bt_tests.h"

#include "utils/datehelper.h"

#include "exceptions/ex_invalid_date.h"
#include "exceptions/ex_notreached.h"

#include "utils/unit_test.h"

#include <iostream>

#define TEST_FLAG(BOOL_EXPR) if (!BOOL_EXPR) { std::cout << "Incorrect flag!" << std::endl; return false; }

bool test_unit_test(){


    ///////////////////
    // BOOL NOT WRAPPED
    ///////////////////


    // TEST
    {
        bool ret = true;
        // mvtodo
    }

    // TEST_TRUE
    {
        bool ret = true;
        // mvtodo
    }

    // TEST_FALSE
    {
        bool ret = true;
        // mvtodo
    }

    // TEST_EX
    {
        bool ret = true;
        // mvtodo
    }

    // TEST_NO_EX
    {
        bool ret = true;
        // mvtodo
    }

    // TEST_ANY_EX
    {
        bool ret = true;
        // mvtodo
    }

    // TEST_ANY_NO_EX
    {
        bool ret = true;
        // mvtodo
    }

    // TEST_EQ
    {
        bool ret = true;
        // mvtodo
    }

    // TEST_NE
    {
        bool ret = true;
        // mvtodo
    }

    // TEST_GT
    {
        bool ret = true;
        // mvtodo
    }

    // TEST_GE
    {
        bool ret = true;
        // mvtodo
    }

    // TEST_LT
    {
        bool ret = true;
        // mvtodo
    }

    // TEST_LE
    {
        bool ret = true;
        // mvtodo
    }


    ///////////////
    // BOOL WRAPPED
    ///////////////


    // TEST
    {
        bool ret = true;
        auto comp = [](auto p1, auto p2) { return (p1 == p2); };
        test(ret, "Must be same", 1, 1, comp);
        TEST_FLAG(ret); // expected: true
    }

    // TEST_EQ
    {
        bool ret = true;
        test_eq(ret, "Must be same", 1, 1);
        TEST_FLAG(ret); // expected: true
    }

    // TEST_NE
    {
        bool ret = true;
        test_ne(ret, "Must not be equal", 2, 4);
        TEST_FLAG(ret); // expected: true
    }

    // TEST_EX
    {
        bool ret = true;
        auto p = []() { throw 1; };
        test_ex<int>(ret, "Must throw int", p);
        TEST_FLAG(ret); // expected: true
    }

    // TEST_NO_EX
    {
        bool ret = true;
        auto p = []() { throw 1; };
        test_no_ex<double>(ret, "Must NOT throw double", p);
        TEST_FLAG(ret); // expected: true
    }

    // TEST_ANY_EX
    {
        bool ret = true;
        auto p = []() { /* i dont throw */ };
        test_any_ex(ret, "IF THIS FAILS, IT'S A SUCCESS! Should fail when no exception is thrown", p);
        TEST_FLAG(!ret); // expected: false
    }

    // TEST_ANY_NO_EX
    {
        bool ret = true;
        auto p_int = []() { throw 1; };
        auto p_double = []() { throw 1.1; };
        test_any_no_ex(ret, "IF THIS FAILS, IT'S A SUCCESS! Should fail when INT exception is thrown", p_int);
        TEST_FLAG(!ret); // expected: false
        test_any_no_ex(ret, "IF THIS FAILS, IT'S A SUCCESS! Should fail when DOUBLE exception is thrown", p_double);
        TEST_FLAG(!ret); // expected: false
    }

    // TEST_TRUE
    {
        bool ret = true;
        test_true(ret, "Must be true", true);
        TEST_FLAG(ret);// expected: true
    }

    // TEST_FALSE
    {
        bool ret = true;
        test_false(ret, "Must be false", false);
        TEST_FLAG(ret); // expected: true
    }

    // TEST_EQ
    {
        bool ret = true;
        test_eq(ret, "Must be equal", true, true);
        TEST_FLAG(ret); // expected: true
    }

    // TEST_GT
    {
        bool ret = true;
        test_gt(ret, "Must be greater than", 2, 1);
        TEST_FLAG(ret); // expected: true
    }

    // TEST_GE
    {
        bool ret = true;
        test_ge(ret, "Must be greater-or-equal", 2, 2);
        TEST_FLAG(ret); // expected: true
    }

    // TEST_LT
    {
        bool ret = true;
        test_lt(ret, "Must be lesser than", 1, 2);
        TEST_FLAG(ret); // expected: true
    }

    // TEST_LE
    {
        bool ret = true;
        test_le(ret, "Must be lesser-or-equal", 2, 2);
        TEST_FLAG(ret); // expected: true
    }

    return true;

}

bool test_datehelper(){

    // test date validator
    bool total = true;
    bool each = true; // mvtodo: remove this, port all old tests to unit_test

    // date should be valid
    {
        //test_eq("Date should be valid", DateHelper::isValidDate(22, 6, 1997), true);
        test_true(total, "Date should be valid", DateHelper::isValidDate(22, 6, 1997));
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
    test_no_ex<Ex_Invalid_Date>(total, "Should not raise exception", [](){ DateHelper dh{7, 5, 1985}; });
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

bool test_accrue(bool &flag_holder, bool func){
    flag_holder &= func;
}

bool test_all(){

    bool acc = true;

    test_accrue(acc, test_unit_test());
    //test_accrue(acc, test_datehelper());

    return acc;
}
