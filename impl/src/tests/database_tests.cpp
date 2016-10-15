
#include "tests/database_tests.h"
#include "utils/sysutils.h"

#include "exceptions/ex_tests_error.h"
#include "exceptions/ex_database_error.h"

#include "testforecho.h"

using strvec = std::vector<std::string>;
using strvec2 = std::vector<strvec>;

bool test_database(){

    bool total {true};

    PRINT_INFO("Testing database...")

    // test investors
    {

        // setup
        DatabaseTestInternal dbt{}; strvec2 res;

        // name
        dbt.db.exec("SELECT name FROM investors WHERE pk_investor = 1", res);
        test_eq(total, "Name retrieved from database should match", res[0][0], "fname1");
        res.clear();

        // email
        dbt.db.exec("SELECT email FROM investors WHERE pk_investor = 2", res);
        test_eq(total, "Email retrieved from database should match", res[0][0], "cname2@company.org");
        res.clear();

        // description
        dbt.db.exec("SELECT description FROM investors WHERE pk_investor = 3", res);
        test_eq(total, "Description retrieved from database should match", res[0][0], "no_data");
        res.clear();

        // date_of_inclusion
        dbt.db.exec("SELECT date_of_inclusion FROM investors WHERE pk_investor = 1", res);
        test_eq(total, "Date of inclusion retrieved from database should match", res[0][0], "06/02/1991");
        res.clear();

    }

    // test subjects
    {

        // setup
        DatabaseTestInternal dbt{}; strvec2 res;

        // tag
        dbt.db.exec("SELECT tag FROM subjects WHERE pk_subject = 1", res);
        test_eq(total, "Tag retrieved from database should match", res[0][0], "prod");
        res.clear();

        // description
        dbt.db.exec("SELECT description FROM subjects WHERE pk_subject = 2", res);
        test_eq(total, "Description retrieved from database should match", res[0][0], "defending");
        res.clear();

        // date_of_inclusion
        dbt.db.exec("SELECT date_of_inclusion FROM subjects WHERE pk_subject = 3", res);
        test_eq(total, "Date of inclusion retrieved from database should match", res[0][0], "17/04/2015");
        res.clear();

    }

    // test currencies
    {

        // setup
        DatabaseTestInternal dbt{}; strvec2 res;

        // label
        dbt.db.exec("SELECT label FROM currencies WHERE pk_currency = 1", res);
        test_eq(total, "Label retrieved from database should match", res[0][0], "usd");
        res.clear();

        // description
        dbt.db.exec("SELECT description FROM currencies WHERE pk_currency = 2", res);
        test_eq(total, "Description retrieved from database should match", res[0][0], "swiss franc");
        res.clear();

        // date_of_inclusion
        dbt.db.exec("SELECT date_of_inclusion FROM currencies WHERE pk_currency = 3", res);
        test_eq(total, "Date of inclusion retrieved from database should match", res[0][0], "04/03/2012");
        res.clear();

    }

    // test invested time
    {

        // setup
        DatabaseTestInternal dbt{}; strvec2 res;

        // invalid currency, must throw exception for violating a constraint
        {
            auto p = [&dbt]() {
                dbt.db.exec("INSERT INTO invested_time(fk_investor, fk_currency, date, description, comment, minutes, price_per_unit) VALUES(1, 4, \"07/02/2014\", \"test\", \"no comment\", 20, 1.25);");
            };
            test_ex<Ex_Database_Error>(total, "Should throw exception when trying to violate a foreign key constraint", p);
            res.clear();
        }

        // invalid investor, must throw exception for violating a constraint
        {
            auto p = [&dbt]() {
                dbt.db.exec("INSERT INTO invested_time(fk_investor, fk_currency, date, description, comment, minutes, price_per_unit) VALUES(10, 2, \"07/02/2014\", \"test\", \"no comment\", 20, 1.25);");
            };
            test_ex<Ex_Database_Error>(total, "Should throw exception when trying to violate a foreign key constraint", p);
            res.clear();
        }

    }

    // test invested time subject link
    {

        // setup
        DatabaseTestInternal dbt{}; strvec2 res;

        // invalid invested time entry, must throw exception for violating a constraint
        {

            auto p = [&dbt]() {
                dbt.db.exec("INSERT INTO invested_time_subjects_link(fk_invested_time, fk_subject) VALUES(50, 25);");
            };
            test_ex<Ex_Database_Error>(total, "Should throw exception when trying to violate a foreign key constraint", p);
            res.clear();

        }

    }

    // test invested assets
    {

        // setup
        DatabaseTestInternal dbt{}; strvec2 res;

        // test inserting valid asset
        {

            auto p = [&dbt]() {
                dbt.db.exec("INSERT INTO invested_assets(fk_investor, fk_currency, date, short_name, description, comment, price) VALUES(3, 3, \"03/06/1967\", \"artsy stuff\", \"nope\", \"irrelevant\", 80);");
            };
            test_no_ex<Ex_Database_Error>(total, "Should not throw exception when inserting a valid, constraint-compliant entry", p);
            res.clear();

        }

        // test inserting invalid asset
        {

            auto p = [&dbt]() {
                dbt.db.exec("INSERT INTO invested_assets(fk_investor, fk_currency, date, short_name, description, comment, price) VALUES(30, 3, \"03/06/1967\", \"artsy stuff\", \"nope\", \"irrelevant\", 80);");
            };
            test_ex<Ex_Database_Error>(total, "Should throw exception when trying to violate a foreign key constraint", p);
            res.clear();

        }

    }

    // test invested assets subjects link
    {

        // setup
        DatabaseTestInternal dbt{}; strvec2 res;

        // test attempted constraint violation
        {

            auto p = [&dbt]() {
                dbt.db.exec("INSERT INTO invested_assets_subjects_link(fk_invested_asset, fk_subject) VALUES(45, 20);");
            };
            test_ex<Ex_Database_Error>(total, "Should throw exception when trying to violate a foreign key constraint", p);
            res.clear();

        }

    }

    // test bonuses
    {

        // setup
        DatabaseTestInternal dbt{}; strvec2 res;

        // test inserting valid bonus
        {

            auto p = [&dbt]() {
                dbt.db.exec("INSERT INTO bonuses(fk_investor, date, short_name, description, comment, reward) VALUES(3, \"08/08/2007\", \"a little something\", \"ok\", \"commenting\", \"time off\");");
            };
            test_no_ex<Ex_Database_Error>(total, "Should not throw exception when inserting a valid, constraint-compliant entry", p);
            res.clear();

        }

        // test inserting invalid bonus
        {

            auto p = [&dbt]() {
                dbt.db.exec("INSERT INTO bonuses(fk_investor, date, short_name, description, comment, reward) VALUES(7, \"08/08/2007\", \"a little something\", \"ok\", \"commenting\", \"time off\");");
            };
            test_ex<Ex_Database_Error>(total, "Should throw exception when trying to violate a foreign key constraint", p);
            res.clear();

        }

    }

    // test bonuses subjects link
    {

        // setup
        DatabaseTestInternal dbt{}; strvec2 res;

        // test attempted constraint violation
        {

            auto p = [&dbt]() {
                dbt.db.exec("INSERT INTO bonuses_subjects_link(fk_bonus, fk_subject) VALUES(45, 20);");
            };
            test_ex<Ex_Database_Error>(total, "Should throw exception when trying to violate a foreign key constraint", p);
            res.clear();

        }

    }

    // test invested money
    {

        // setup
        DatabaseTestInternal dbt{}; strvec2 res;

        // test inserting valid invested money
        {

            auto p = [&dbt]() {
                dbt.db.exec("INSERT INTO invested_money(fk_investor, fk_currency, date, short_name, description, comment, amount) VALUES(1, 1, \"22/03/1996\", \"cash\", \"cold hard cash\", \"nop\", 350.75);");
            };
            test_no_ex<Ex_Database_Error>(total, "Should not throw exception when inserting a valid, constraint-compliant entry", p);
            res.clear();

        }

        // test inserting invalid asset
        {

            auto p = [&dbt]() {
                dbt.db.exec("INSERT INTO invested_money(fk_investor, fk_currency, date, short_name, description, comment, amount) VALUES(30, 22, \"22/03/1996\", \"cash\", \"cold hard cash\", \"nop\", 350.75);");
            };
            test_ex<Ex_Database_Error>(total, "Should throw exception when trying to violate a foreign key constraint", p);
            res.clear();

        }

    }

    // test invested money subjects link
    {

        // setup
        DatabaseTestInternal dbt{}; strvec2 res;

        // test attempted constraint violation
        {

            auto p = [&dbt]() {
                dbt.db.exec("INSERT INTO invested_money_subjects_link(fk_invested_money, fk_subject) VALUES(45, 24);");
            };
            test_ex<Ex_Database_Error>(total, "Should throw exception when trying to violate a foreign key constraint", p);
            res.clear();

        }

    }

    return total;

}

DatabaseTestInternal::DatabaseTestInternal():
db_path{"/tmp/test.db"}, db{}
{

    if (fileExists(db_path)){
        EX_THROW(Ex_Tests_Error, "Fatal testing error: " + db_path + " already exists")
    }

    db.db_path = db_path;
    db.open_database();
    load_test_data();
}

DatabaseTestInternal::~DatabaseTestInternal(){
    if (fileExists(db_path)){
        fileDelete(db_path);
    }
}

void DatabaseTestInternal::load_test_data(){

    /*
    @investors
    name TEXT NOT NULL,
    email TEXT,
    description TEXT,
    date_of_inclusion TEXT
    */

    db.exec("INSERT INTO investors(name, email, description, date_of_inclusion) VALUES(\"fname1\", \"fname1@company.org\", \"no_desc\", \"06/02/1991\");");
    db.exec("INSERT INTO investors(name, email, description, date_of_inclusion) VALUES(\"cname2\", \"cname2@company.org\", \"no_desk\", \"03/08/1985\");");
    db.exec("INSERT INTO investors(name, email, description, date_of_inclusion) VALUES(\"bname7\", \"bname7@company.org\", \"no_data\", \"05/12/1941\");");

    /*
    @subjects
    tag TEXT NOT NULL,
    description TEXT,
    date_of_inclusion TEXT
    */

    db.exec("INSERT INTO subjects(tag, description, date_of_inclusion) VALUES(\"prod\", \"running\", \"17/04/2015\");");
    db.exec("INSERT INTO subjects(tag, description, date_of_inclusion) VALUES(\"wargame\", \"defending\", \"16/05/2013\");");
    db.exec("INSERT INTO subjects(tag, description, date_of_inclusion) VALUES(\"prod\", \"running\", \"17/04/2015\");");

    /*
    @currencies
    label TEXT NOT NULL,
    description TEXT,
    date_of_inclusion TEXT
    */

    db.exec("INSERT INTO currencies(label, description, date_of_inclusion) VALUES(\"usd\", \"us dollar\", \"04/03/2010\");");
    db.exec("INSERT INTO currencies(label, description, date_of_inclusion) VALUES(\"chf\", \"swiss franc\", \"04/03/2011\");");
    db.exec("INSERT INTO currencies(label, description, date_of_inclusion) VALUES(\"nzd\", \"new zealand dollar\", \"04/03/2012\");");

    /*
    @invested_time
    fk_investor INTEGER NOT NULL,
    fk_currency INTEGER NOT NULL,
    date TEXT,
    description TEXT,
    comment TEXT,
    minutes INTEGER,
    price_per_unit REAL
    */

    db.exec("INSERT INTO invested_time(fk_investor, fk_currency, date, description, comment, minutes, price_per_unit) VALUES(1, 1, \"07/02/2014\", \"test\", \"no comment\", 20, 1.25);");
    db.exec("INSERT INTO invested_time(fk_investor, fk_currency, date, description, comment, minutes, price_per_unit) VALUES(2, 3, \"07/02/2011\", \"test\", \"no comment\", 25, 1.20);");

    /*
    @invested_time_subjects_link
    fk_invested_time INTEGER NOT NULL,
    fk_subject INTEGER NOT NULL
    */

    db.exec("INSERT INTO invested_time_subjects_link(fk_invested_time, fk_subject) VALUES(1, 1);");

    /*
    @invested_assets
    fk_investor INTEGER NOT NULL,
    fk_currency INTEGER NOT NULL
    date TEXT,
    short_name TEXT,
    description TEXT,
    comment TEXT,
    price REAL
    */

    db.exec("INSERT INTO invested_assets(fk_investor, fk_currency, date, short_name, description, comment, price) VALUES(2, 1, \"03/06/1967\", \"artsy stuff\", \"nope\", \"irrelevant\", 80);");
    db.exec("INSERT INTO invested_assets(fk_investor, fk_currency, date, short_name, description, comment, price) VALUES(3, 1, \"03/06/1957\", \"posters\", \"nopez\", \"irrelevant\", 120);");

    /*
    @invested_assets_subjects_link
    fk_invested_asset INTEGER NOT NULL,
    fk_subject INTEGER NOT NULL
    */

    db.exec("INSERT INTO invested_assets_subjects_link(fk_invested_asset, fk_subject) VALUES(1, 1);");

    /*
    @bonuses
    fk_investor INTEGER NOT NULL,
    date TEXT,
    short_name TEXT,
    description TEXT,
    comment TEXT,
    reward TEXT
    */

    db.exec("INSERT INTO bonuses(fk_investor, date, short_name, description, comment, reward) VALUES(2, \"08/08/2007\", \"a little something\", \"ok\", \"commenting\", \"time off\");");

    /*
    @bonuses_subjects_link
    fk_bonus INTEGER NOT NULL,
    fk_subject INTEGER NOT NULL
    */

    db.exec("INSERT INTO bonuses_subjects_link(fk_bonus, fk_subject) VALUES(1, 3);");

    /*
    @invested_money
    fk_investor INTEGER NOT NULL,
    fk_currency INTEGER NOT NULL,
    date TEXT,
    short_name TEXT,
    description TEXT,
    comment TEXT,
    amount REAL
    */

    db.exec("INSERT INTO invested_money(fk_investor, fk_currency, date, short_name, description, comment, amount) VALUES(3, 2, \"22/03/1996\", \"cash\", \"cold hard cash\", \"nop\", 350.75);");

    /*
    @invested_money_subjects_link
    fk_invested_money INTEGER NOT NULL,
    fk_subject INTEGER NOT NULL
    */

    db.exec("INSERT INTO invested_money_subjects_link(fk_invested_money, fk_subject) VALUES(1, 1);");

}
