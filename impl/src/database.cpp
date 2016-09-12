
#include "database.h"
#include "exceptions/ex_failed_opening_database.h"
#include "exceptions/ex_database_error.h"
#include "utils/sysutils.h"

#include <vector>

int exec_callback(void *notused, int argc, char **argv, char **col_name){

    (void)notused;

    // mvtodo: finish this
    for (int i = 0; i < argc; i++){
        printf("%s = %s\n", col_name[i], argv[i] ? argv[i] : "NULL");
    }

    return 0;
}

Database::Database(const std::string &connection):sqlite_con{0}{

    // will pre-load the newly created database
    // with a schema template
    bool bs = !(fileExists(connection));

    int rc {sqlite3_open(connection.c_str(), &sqlite_con)};
    if (rc){
        sqlite3_close(sqlite_con);
        EX_THROW(Ex_FailedOpeningDatabase, "Failed opening the database: " + connection);
    }

    // enable foreign keys
    std::string msg;
    if (!exec("PRAGMA foreign_keys = ON;",  msg)){
        EX_THROW(Ex_Database_Error, msg);
    }

    if (bs) {bootstrap();}

}

Database::~Database(){
    sqlite3_close(sqlite_con);
}

void Database::bootstrap(){

    std::vector<std::string> cmds;
    cmds.push_back("CREATE TABLE investors (pk_investor INTEGER PRIMARY KEY, name TEXT, email TEXT, description TEXT, date_of_inclusion TEXT);");
    cmds.push_back("CREATE TABLE subjects (pk_subject INTEGER PRIMARY KEY, tag TEXT, description TEXT, date_of_inclusion TEXT);");
    cmds.push_back("CREATE TABLE currencies (pk_currency INTEGER PRIMARY KEY, label TEXT, description TEXT, date_of_inclusion TEXT);");

    cmds.push_back("CREATE TABLE invested_time (pk_invested_time INTEGER PRIMARY KEY, fk_investor INTEGER, fk_currency INTEGER, date TEXT, description TEXT, comment TEXT, minutes INTEGER, price_per_unit REAL, FOREIGN KEY(fk_investor) REFERENCES investors(pk_investor), FOREIGN KEY(fk_currency) REFERENCES currencies(pk_currency));");
    cmds.push_back("CREATE TABLE invested_time_subjects_link (fk_invested_time INTEGER, fk_subject INTEGER, PRIMARY KEY (fk_invested_time, fk_subject), FOREIGN KEY(fk_invested_time) REFERENCES invested_time(pk_invested_time), FOREIGN KEY(fk_subject) REFERENCES subjects(pk_subject));");

    cmds.push_back("CREATE TABLE invested_assets (pk_invested_asset INTEGER PRIMARY KEY, fk_investor INTEGER, fk_currency INTEGER, date TEXT, short_name TEXT, description TEXT, comment TEXT, price REAL, FOREIGN KEY(fk_investor) REFERENCES investors(pk_investor), FOREIGN KEY(fk_currency) REFERENCES currencies(pk_currency));");
    cmds.push_back("CREATE TABLE invested_assets_subjects_link (fk_invested_asset INTEGER, fk_subject INTEGER, PRIMARY KEY (fk_invested_asset, fk_subject), FOREIGN KEY(fk_invested_asset) REFERENCES invested_assets(pk_invested_asset), FOREIGN KEY(fk_subject) REFERENCES subjects(pk_subject));");

    cmds.push_back("CREATE TABLE bonuses (pk_bonus INTEGER PRIMARY KEY, fk_investor INTEGER, date TEXT, short_name TEXT, description TEXT, comment TEXT, reward TEXT, FOREIGN KEY(fk_investor) REFERENCES investors(pk_investor));");
    cmds.push_back("CREATE TABLE bonuses_subjects_link (fk_bonus INTEGER, fk_subject INTEGER, PRIMARY KEY (fk_bonus, fk_subject), FOREIGN KEY(fk_bonus) REFERENCES bonuses(pk_bonus), FOREIGN KEY(fk_subject) REFERENCES subjects(pk_subject));");

    cmds.push_back("CREATE TABLE invested_money (pk_invested_money INTEGER PRIMARY KEY, fk_investor INTEGER, fk_currency INTEGER, date TEXT, short_name TEXT, description TEXT, comment TEXT, amount REAL, FOREIGN KEY(fk_investor) REFERENCES investors(pk_investor), FOREIGN KEY(fk_currency) REFERENCES currencies(pk_currency));");
    cmds.push_back("CREATE TABLE invested_money_subjects_link (fk_invested_money INTEGER, fk_subject INTEGER, PRIMARY KEY (fk_invested_money, fk_subject), FOREIGN KEY(fk_invested_money) REFERENCES invested_money(pk_invested_money), FOREIGN KEY(fk_subject) REFERENCES subjects(pk_subject));");

    std::string errmsg;
    for (auto i: cmds){
        if (!exec(i.c_str(), errmsg)){
            EX_THROW(Ex_Database_Error, errmsg);
        }
    }

}

bool Database::exec(const std::string &sql, std::string &return_msg){

    char *msg;
    int rc {sqlite3_exec(sqlite_con, sql.c_str(), exec_callback, 0, &msg)};

    if (rc != SQLITE_OK){
        return_msg = msg;
        sqlite3_free(msg);
        return false;
    }

    return true;
}
