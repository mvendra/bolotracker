
#include "tests/model_tests.h"
#include "dataobjects/dataobjects.h"

#include "utils/sysutils.h"

#include "exceptions/ex_tests_error.h"

#include "testforecho.h"

bool test_model(){

    bool total {true};

    ModelTestInternal mti{};

    // test investor
    {
        test_true(total, "Must have the passed investor name", mti.model.has_investor("jon"));
        test_false(total, "Must not have the passed investor name", mti.model.has_investor("bolo"));

        mti.model.add_investor("added", "added@dogs.com", "test13", DateHelper("06/07/2017"));
        Investor inv{0, "", "", "", DateHelper{}};

        test_true(total, "Must have the recently added investor.", mti.model.get_investor_info("added", inv));
        test_eq(total, "Name must match", "added", inv.name);
        test_eq(total, "Email must match", "added@dogs.com", inv.email);
        test_eq(total, "Description must match", "test13", inv.description);
        test_eq(total, "Date must match", DateHelper("06/07/2017").getDateString(), inv.date_of_inclusion.getDateString());
        test_false(total, "Must not have some random name", mti.model.get_investor_info("i-dont-exist", inv));
    }

    // test subject
    {
        test_true(total, "Must have the passed subject tag", mti.model.has_subject("qa"));
        test_false(total, "Must not have the passed subject tag", mti.model.has_subject("rubbish"));

        mti.model.add_subject("bugs", "nasty defects", DateHelper("01/01/2005"));
        Subject subj{0, "", "", DateHelper{}};

        test_true(total, "Must have the recently added subject", mti.model.get_subject_info("bugs", subj));
        test_eq(total, "Tag must match", "bugs", subj.tag);
        test_eq(total, "Description must match", "nasty defects", subj.description);
        test_eq(total, "Date must match", DateHelper("01/01/2005").getDateString(), subj.date_of_inclusion.getDateString());
        test_false(total, "Must not have some random tag", mti.model.get_subject_info("lalala", subj));

    }

    // test currency
    {
        test_true(total, "Must have the passed subject currency label", mti.model.has_currency("cad"));
        test_false(total, "Must not have the passed currency label", mti.model.has_subject("eur"));

        mti.model.add_currency("nok", "norwegian krone", DateHelper("01/01/2006"));
        Currency curr{0, "", "", DateHelper{}};

        test_true(total, "Must have the recently added currency", mti.model.get_currency_info("nok", curr));
        test_eq(total, "Label must match", "nok", curr.label);
        test_eq(total, "Description must match", "norwegian krone", curr.description);
        test_eq(total, "Date must match", DateHelper("01/01/2006").getDateString(), curr.date_of_inclusion.getDateString());
        test_false(total, "Must not have some random label", mti.model.get_currency_info("clp", curr));

    }

    // test invested time
    {

        // mvtodo: add some, then try to retrieve, with dirty checking.

        std::vector<InvestedTime> vec_inv_time;
        mti.model.get_invested_time_by_investor("jon", vec_inv_time);
        int stop=1; // mvdebug
        (void)stop; // mvdebug
    }

    return total;

}

ModelTestInternal::ModelTestInternal():connection{"/tmp/test_model.db"}, model{}
{
    if (fileExists(connection)){
        EX_THROW(Ex_Tests_Error, "Fatal testing error: " + connection + " already exists")
    }

    model.connection = connection;
    model.open_database();
    load_test_data();
}

ModelTestInternal::~ModelTestInternal(){
    if (fileExists(connection)){
        fileDelete(connection);
    }
}

void ModelTestInternal::load_test_data(){
    try {
        load_test_data_delegate();
    } catch(...){
        EX_THROW(Ex_Tests_Error, "Failed loading test model data")
    }
}

void ModelTestInternal::load_test_data_delegate(){

    // investors
    model.add_investor("jon", "jon@thecat.com", "test1", DateHelper("06/07/2006"));
    model.add_investor("libras", "libras@perfectcircle.com", "test2", DateHelper("06/07/2003"));
    model.add_investor("a-nother", "mail-less", "test3", DateHelper("06/07/1337"));

    // subjects
    model.add_subject("dev", "test4", DateHelper("09/09/2016"));
    model.add_subject("qa", "test5", DateHelper("09/09/2016"));
    model.add_subject("release", "test6", DateHelper("09/09/2016"));

    // currencies
    model.add_currency("aud", "straya dollar", DateHelper("07/02/2001"));
    model.add_currency("nan", "not a number", DateHelper("07/02/2002"));
    model.add_currency("cad", "maple dollar", DateHelper("07/02/2003"));

    // invested time
    model.add_invested_time(1, 1, DateHelper("15/02/2002"), "no desc", "no comment", 25, 1.25);
    model.add_invested_time(2, 3, DateHelper("15/02/2002"), "no desc", "no comment", 50, 45);

    // intested time subject link
    model.attach_subject_to_invested_time(1, 1);

    // invested assets
    model.add_invested_asset(1, 1, DateHelper("12/02/2005"), "some ideas", "desc", "no", 70.1);

    // invested assets subjects link
    model.attach_subject_to_invested_asset(1, 2);

    // bonuses
    model.add_bonus(3, DateHelper("01/03/2012"), "bono-bo", "desc", "koment", "wine");

    // bonuses subjects link
    model.attach_subject_to_bonus(1, 3);

    // invested money
    model.add_invested_money(2, 1, DateHelper("25/12/2008"), "shortnames", "some desc", "commenting", 300);

    // invested money subjects link
    model.attach_subject_to_invested_money(1, 3);

}
