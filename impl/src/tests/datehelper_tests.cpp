
#include "tests/datehelper_tests.h"

#include "utils/datehelper.h"

#include "exceptions/ex_invalid_date.h"
#include "exceptions/ex_notreached.h"

#include "testforecho.h"

using namespace testforecho;

unsigned int test_datehelper(){

    // test date validator
    unsigned int total {0};

    PRINT_INFO("Testing DateHelper...")

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
        test_neq(total, "Conversion should fail", 3, d);
        test_neq(total, "Conversion should fail", 4, m);
        test_neq(total, "Conversion should fail", 2005, y);
    }

    // should throw exacly that type of exception
    {
        T4E_MAKE_0(p, {DateHelper dh{7, 80, 1978};} )
        test_ex<Ex_Invalid_Date>(total, "Should raise exception", T4E_GET(p));
    }

    // should throw exception when trying to set bad date
    {
        T4E_MAKE_0(p, { DateHelper dh{7, 5, 1985}; dh.setDate("35/20/2000"); } )
        test_ex<Ex_Invalid_Date>(total, "Should raise exception", T4E_GET(p));
    }

    // should return the same text date as the one passed during construction
    {
        const std::string templ {"03/03/1993"};
        DateHelper dh{templ};
        test_eq(total, "Init date and later fetched date should match", templ, dh.getDateString());
    }

    T4E_MAKE_0(p_inv_date, { DateHelper dh{7, 5, 1985}; dh.setDate("35/20/2000"); } )
    test_ex<Ex_Invalid_Date>(total, "Should raise exception", T4E_GET(p_inv_date));
    T4E_MAKE_0(p_v_date, { DateHelper dh{7, 5, 1985}; } )
    test_no_ex<Ex_Invalid_Date>(total, "Should not raise exception", T4E_GET(p_v_date));

    // should be able to set its own date with the present
    {
        DateHelper dh{};
        test_true(total, "Auto-built date should be valid", DateHelper::isValidDate(dh.getDateString()));
    }

    // copy ctor and attrib op should work
    {
        DateHelper dh1{"01/01/2004"};
        DateHelper dh2 = dh1;
        test_eq(total, "Should match by the attribute copy", dh1.getDateString(), dh2.getDateString());
        DateHelper dh3{dh2};
        test_eq(total, "Should match by the copy constructor", dh2.getDateString(), dh3.getDateString());
    }

    return total;

}
