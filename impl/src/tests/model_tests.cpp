
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

        mti.model.add_invested_time(1, 2, DateHelper{"01/02/1998"}, "otter desc", "some comment", 1222, 99.76);
        // the pk = 3 below is meant to be the invested time we just added (just above this line)
        // just should stay consistent with the load_test_data_delegate() stuff.
        // if a breakage ever occurs, it would suffice to re-instantiate the test model here (to reset the test data,
        // effectively guaranteeing a pk of 3 for the just-added invested time entry)
        mti.model.attach_subject_to_invested_time(3, 1);

        std::vector<InvestedTime> vec_inv_time;

        auto p_ = [&total, &vec_inv_time](){
            test_eq(total, "Added invested time must belong to the right investor", vec_inv_time[1].fk_investor, 1);
            test_eq(total, "Added invested time must carry the chosen currency", vec_inv_time[1].fk_currency, 2);
            test_eq(total, "Added invested time's date must match", vec_inv_time[1].date.getDateString(), DateHelper{"01/02/1998"}.getDateString());
            test_eq(total, "Added invested time's description must match", vec_inv_time[1].description, "otter desc");
            test_eq(total, "Added invested time's comment must match", vec_inv_time[1].comment, "some comment");
            test_eq(total, "Added invested time's minutes must match", vec_inv_time[1].minutes, 1222);
            test_eq(total, "Added invested time's price per unit must match", vec_inv_time[1].price_per_unit, 99.76);
        };

        test_true(total, "Investor must have invested time", mti.model.get_invested_time_by_investor("jon", vec_inv_time));
        p_();
        vec_inv_time.clear();

        test_true(total, "Investor must have invested time", mti.model.get_invested_time_by_investor(1, vec_inv_time));
        p_();

        std::vector<Subject> subjs;
        test_true(total, "Must have subjects attached", mti.model.get_invested_time_subjects(3, subjs));
        test_eq(total, "Must have the attached subject", subjs[0].tag, "dev");

    }

    // invested assets
    {
        mti.model.add_invested_asset(2, 3, DateHelper{"01/02/1978"}, "shortened name", "yet more desc", "and comment", 26.1);
        mti.model.attach_subject_to_invested_asset(2, 1); // pk = 2 here depends on the previous line

        std::vector<InvestedAsset> vec_inv_as;

        auto p_ = [&total, &vec_inv_as]() {
            test_eq(total, "Added invested asset must belong to the right investor", vec_inv_as[0].fk_investor, 2);
            test_eq(total, "Added invested asset's currency must match", vec_inv_as[0].fk_currency, 3);
            test_eq(total, "Added invested asset's date much match", vec_inv_as[0].date.getDateString(), "01/02/1978");
            test_eq(total, "Added invested asset's short name must match", vec_inv_as[0].short_name, "shortened name");
            test_eq(total, "Added invested asset's description must match", vec_inv_as[0].description, "yet more desc");
            test_eq(total, "Added invested asset's comment must match", vec_inv_as[0].comment, "and comment");
            test_eq(total, "Added invested asset's price must match", vec_inv_as[0].price, 26.1);
        };

        test_true(total, "Investor must have invested asset", mti.model.get_invested_assets_by_investor("libras", vec_inv_as));
        p_();
        vec_inv_as.clear();

        test_true(total, "Investor must have invested asset", mti.model.get_invested_assets_by_investor(2, vec_inv_as));
        p_();

        std::vector<Subject> subjs;
        test_true(total, "Must have subjects attached", mti.model.get_invested_asset_subjects(2, subjs));
        test_eq(total, "Must have the attached subject", subjs[0].tag, "dev");

    }

    // bonuses
    {

        mti.model.add_bonus(3, DateHelper{"01/05/1973"}, "lack of creativity", "this is getting old", "im tired of this", "doggie treats");
        mti.model.attach_subject_to_bonus(2, 3); // pk = 2 here depends on the previous line

        std::vector<Bonus> vec_bn;

        auto p_ = [&total, &vec_bn]() {
            test_eq(total, "Added bonus must belong to the right investor", vec_bn[1].fk_investor, 3);
            test_eq(total, "Added bonus's date much match", vec_bn[1].date.getDateString(), "01/05/1973");
            test_eq(total, "Added bonus's short name must match", vec_bn[1].short_name, "lack of creativity");
            test_eq(total, "Added bonus's description must match", vec_bn[1].description, "this is getting old");
            test_eq(total, "Added bonus's comment must match", vec_bn[1].comment, "im tired of this");
            test_eq(total, "Added bonus's reward must match", vec_bn[1].reward, "doggie treats");
        };

        test_true(total, "Investor must have bonus", mti.model.get_bonuses_by_investor("a-nother", vec_bn));
        p_();
        vec_bn.clear();

        test_true(total, "Investor must have bonus", mti.model.get_bonuses_by_investor(3, vec_bn));
        p_();

        std::vector<Subject> subjs;
        test_true(total, "Must have subjects attached", mti.model.get_bonus_subjects(2, subjs));
        test_eq(total, "Must have the attached subject", subjs[0].tag, "release");

    }

    // invested money
    {
        // mvtodo
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

    // remember you MAY NOT freely scramble these around, or it will mess up
    // the pks the records will get. many tests depend on fixed/expected
    // pks to run correctly

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
