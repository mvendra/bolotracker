
#include "tests/datehelper_tests.h"

#include "utils/datehelper.h"

#include "exceptions/ex_invalid_date.h"
#include "exceptions/ex_notreached.h"

#include "testforecho.h"

bool test_datehelper(){

    // test date validator
    bool total {true};

    // date should be valid
    test_true(total, "Date should be valid", DateHelper::isValidDate(22, 6, 1997));
    test_true(total, "Date should be valid", DateHelper::isValidDate(22, 6, 1997));

    // date should be invalid
    test_false(total, "Date should be invalid", DateHelper::isValidDate(32, 6, 1997));

    // date should be valid
    test_true(total, "Date should be valid", DateHelper::isValidDate("05/08/2001"));

    // date should be invalid
    test_false(total, "Date should be invalid", DateHelper::isValidDate("05/13/1985"));

    // conversion from number to text should succeed
    test_eq(total, "Conversion should succeed", "06/03/2002", DateHelper::convertFromNumbers(6, 3, 2002));

    // conversion from text to number should succeed
    {
        unsigned short d{0}, m{0}, y{0};
        DateHelper::convertFromText("07/02/2003", d, m, y);
        test_eq(total, "Conversion should succeed", 7, d);
        test_eq(total, "Conversion should succeed", 2, m);
        test_eq(total, "Conversion should succeed", 2003, y);
    }

    // conversion from text to number should fail
    {
        unsigned short d{3}, m{4}, y{2005};
        DateHelper::convertFromText("nope", d, m, y);
        test_ne(total, "Conversion should fail", 3, d);
        test_ne(total, "Conversion should fail", 4, m);
        test_ne(total, "Conversion should fail", 2005, y);
    }

    // should throw exacly that type of exception
    {
        auto p = []() { DateHelper dh{7, 80, 1978}; };
        test_ex<Ex_Invalid_Date>(total, "Should raise exception", p);
    }

    // should throw exception when trying to set bad date
    {
        auto p = []() { DateHelper dh{7, 5, 1985}; dh.setDate("35/20/2000"); };
        test_ex<Ex_Invalid_Date>(total, "Should raise exception", p);
    }

    // should return the same text date as the one passed during construction
    {
        const std::string templ {"03/03/1993"};
        DateHelper dh{templ};
        test_eq(total, "Init date and later fetched date should match", templ, dh.getDateString());
    }

    test_ex<Ex_Invalid_Date>(total, "Should raise exception", [](){ DateHelper dh{7, 5, 1985}; dh.setDate("35/20/2000"); });
    test_no_ex<Ex_Invalid_Date>(total, "Should not raise exception", [](){ DateHelper dh{7, 5, 1985}; });

    // should be able to set its own date with the present
    {
        DateHelper dh{};
        test_true(total, "Auto-built date should be valid", DateHelper::isValidDate(dh.getDateString()));
    }

    return total;

}
