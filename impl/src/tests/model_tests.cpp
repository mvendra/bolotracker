
#include "tests/model_tests.h"
#include "tests/database_tests.h"

#include "utils/sysutils.h"

#include "exceptions/ex_tests_error.h"

#include "testforecho.h"

bool test_model(){

    bool total {true};

    {
        // mvtodo: implement
        ModelTestInternal mti{};
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

    // mvdebug begin
#if 0
    DateHelper dh{};

    //model.add_subject("dev", "test", dh);
    //model.add_currency("usd", "test", dh);
    //model.add_investor("bob", "bolo@tracker", "test", dh);
    //model.add_invested_time(1, 1, dh, "no desc", "no comment", 25, 1.25);
    //model.attach_subject_to_invested_time(1, 1);
    //model.add_invested_asset(1, 1, dh, "a little something", "desc", "no", 59.99);
    //model.attach_subject_to_invested_asset(1, 1);
    //model.add_bonus(1, dh, "little bono", "desc", "koment", "pizza");
    model.attach_subject_to_bonus(1, 2);
    // mvdebug end

    // mvdebug begin
    unsigned int pk;
    std::string name;
    std::string email;
    std::string description;
    std::string comment;
    std::string label;
    std::string tag;
    double value;
    DateHelper dh {};

    (void)pk; (void)name; (void)label; (void)tag; (void)email; (void)description; (void)comment; (void)value; (void)dh;

    model.get_investor_info("bob", pk, email, description, dh);
    //model.get_investor_info(1, name, email, description, dh);

    //model.get_subject_info("dev", pk, description, dh);
    //model.get_subject_info(2, tag, description, dh);

    //model.get_currency_info("usd", pk, description, dh);
    //model.get_currency_info(2, label, description, dh);

    //std::cout << "pk: [" << uintToStr(pk) << "]" << std::endl;
    //std::cout << "name: [" << name << "]" << std::endl;
    //std::cout << "email: [" << email << "]" << std::endl;
    //std::cout << "description: [" << description << "]" << std::endl;
    //std::cout << "comment: [" << comment << "]" << std::endl;
    //std::cout << "label: [" << label << "]" << std::endl;
    //std::cout << "tag: [" << tag << "]" << std::endl;
    //std::cout << "date: [" << dh.getDateString() << "]" << std::endl;

    /*
    std::vector<Investor> invs;
    model.get_all_investors(invs);

    for (auto x: invs){
        std::cout << "inv.pk: [" << uintToStr(x.pk_investor) << "]" << std::endl;
        std::cout << "inv.name: [" << x.name << "]" << std::endl;
        std::cout << "inv.email: [" << x.email << "]" << std::endl;
        std::cout << "inv.description: [" << x.description << "]" << std::endl;
        std::cout << "inv.date_of_inclusion: [" << x.date_of_inclusion.getDateString() << "]" << std::endl << std::endl;
    }
    */

    /*
    std::vector<Subject> subjs;
    model.get_all_subjects(subjs);

    for (auto x: subjs){
        std::cout << "subj.pk: [" << uintToStr(x.pk_subject) << "]" << std::endl;
        std::cout << "subj.tag: [" << x.tag << "]" << std::endl;
        std::cout << "subj.description: [" << x.description << "]" << std::endl;
        std::cout << "subj.date_of_inclusion: [" << x.date_of_inclusion.getDateString() << "]" << std::endl << std::endl;
    }
    */

/*
    std::vector<Currency> currs;
    model.get_all_currencies(currs);

    for (auto x: currs){
        std::cout << "curr.pk: [" << uintToStr(x.pk_currency) << "]" << std::endl;
        std::cout << "curr.label: [" << x.label << "]" << std::endl;
        std::cout << "curr.description: [" << x.description << "]" << std::endl;
        std::cout << "curr.date_of_inclusion: [" << x.date_of_inclusion.getDateString() << "]" << std::endl << std::endl;
    }
*/

#endif
    // mvdebug end

}
