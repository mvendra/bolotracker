
#include "database.h"
#include "utils/sysutils.h"
#include "utils/conversions.h"

#include "utils/managedbuffer.h"

#include "exceptions/ex_failed_opening_database.h"
#include "exceptions/ex_failed_closing_database.h"
#include "exceptions/ex_database_error.h"

#include <vector>

using strvec = std::vector<std::string>;
using strvec2 = std::vector<strvec>;

Database::Database():db_path{}, sqlite_con{0}{
}

Database::Database(const std::string &connection):db_path{connection}, sqlite_con{0}{
    open_database();
}

Database::~Database(){
    close_database();
}

void Database::open_database(){

    // will pre-load the newly created database
    // with a schema template
    bool bs = !(fileExists(db_path));

    int rc {sqlite3_open(db_path.c_str(), &sqlite_con)};
    if (rc){
        sqlite3_close(sqlite_con);
        EX_THROW(Ex_FailedOpeningDatabase, "Failed opening the database: " + db_path);
    }

    // enable foreign keys
    exec("PRAGMA foreign_keys = ON;");

    // if this is a new database...
    if (bs) {bootstrap();}

}

void Database::close_database(){
    if (sqlite_con){
        int r = sqlite3_close(sqlite_con);
        if (r != SQLITE_OK) {
            EX_THROW(Ex_FailedClosingDatabase, "Could not close database")
        }
        sqlite_con = 0;
    }
}

void Database::reset(){
    close_database();
    fileDelete(db_path);
    open_database();
}

void Database::bootstrap(){

    std::vector<std::string> cmds;

    cmds.push_back("CREATE TABLE investors (pk_investor INTEGER PRIMARY KEY NOT NULL,name TEXT NOT NULL,email TEXT,description TEXT,date_of_inclusion TEXT,UNIQUE(pk_investor, name));");
    cmds.push_back("CREATE TABLE subjects (pk_subject INTEGER PRIMARY KEY NOT NULL,tag TEXT NOT NULL,description TEXT,date_of_inclusion TEXT,UNIQUE(pk_subject, tag));");
    cmds.push_back("CREATE TABLE currencies (pk_currency INTEGER PRIMARY KEY NOT NULL,label TEXT NOT NULL,description TEXT,date_of_inclusion TEXT,UNIQUE(pk_currency, label));");
    cmds.push_back("CREATE TABLE invested_time (pk_invested_time INTEGER PRIMARY KEY NOT NULL,fk_investor INTEGER NOT NULL,fk_currency INTEGER NOT NULL,date TEXT,description TEXT,comment TEXT,minutes INTEGER,price_per_unit REAL,FOREIGN KEY(fk_investor) REFERENCES investors(pk_investor),FOREIGN KEY(fk_currency) REFERENCES currencies(pk_currency),UNIQUE(pk_invested_time));");
    cmds.push_back("CREATE TABLE invested_time_subjects_link (fk_invested_time INTEGER NOT NULL,fk_subject INTEGER NOT NULL,PRIMARY KEY (fk_invested_time, fk_subject),FOREIGN KEY(fk_invested_time) REFERENCES invested_time(pk_invested_time),FOREIGN KEY(fk_subject) REFERENCES subjects(pk_subject));");
    cmds.push_back("CREATE TABLE invested_assets (pk_invested_asset INTEGER PRIMARY KEY NOT NULL,fk_investor INTEGER NOT NULL,fk_currency INTEGER NOT NULL,date TEXT,short_name TEXT,description TEXT,comment TEXT,price REAL,FOREIGN KEY(fk_investor) REFERENCES investors(pk_investor),FOREIGN KEY(fk_currency) REFERENCES currencies(pk_currency),UNIQUE(pk_invested_asset));");
    cmds.push_back("CREATE TABLE invested_assets_subjects_link (fk_invested_asset INTEGER NOT NULL,fk_subject INTEGER NOT NULL,PRIMARY KEY (fk_invested_asset, fk_subject),FOREIGN KEY(fk_invested_asset) REFERENCES invested_assets(pk_invested_asset),FOREIGN KEY(fk_subject) REFERENCES subjects(pk_subject));");
    cmds.push_back("CREATE TABLE bonuses (pk_bonus INTEGER PRIMARY KEY NOT NULL,fk_investor INTEGER NOT NULL,date TEXT,short_name TEXT,description TEXT,comment TEXT,reward TEXT,FOREIGN KEY(fk_investor) REFERENCES investors(pk_investor),UNIQUE(pk_bonus));");
    cmds.push_back("CREATE TABLE bonuses_subjects_link (fk_bonus INTEGER NOT NULL,fk_subject INTEGER NOT NULL,PRIMARY KEY (fk_bonus, fk_subject),FOREIGN KEY(fk_bonus) REFERENCES bonuses(pk_bonus),FOREIGN KEY(fk_subject) REFERENCES subjects(pk_subject));");
    cmds.push_back("CREATE TABLE invested_money (pk_invested_money INTEGER PRIMARY KEY NOT NULL,fk_investor INTEGER NOT NULL,fk_currency INTEGER NOT NULL,date TEXT,short_name TEXT,description TEXT,comment TEXT,amount REAL,FOREIGN KEY(fk_investor) REFERENCES investors(pk_investor),FOREIGN KEY(fk_currency) REFERENCES currencies(pk_currency),UNIQUE(pk_invested_money));");
    cmds.push_back("CREATE TABLE invested_money_subjects_link (fk_invested_money INTEGER NOT NULL,fk_subject INTEGER NOT NULL,PRIMARY KEY (fk_invested_money, fk_subject),FOREIGN KEY(fk_invested_money) REFERENCES invested_money(pk_invested_money),FOREIGN KEY(fk_subject) REFERENCES subjects(pk_subject));");

    for (auto i: cmds){
        exec(i);
    }

}

void Database::exec(const std::string &sql){
    // handy, and wasteful
    std::vector<std::vector<std::string>> discarded;
    exec(sql, discarded);
}

void Database::exec(const std::string &sql, std::vector<std::vector<std::string>> &result){

    sqlite3_stmt *statement {0};
    int rc;

    rc = sqlite3_prepare_v2(sqlite_con, sql.c_str(), sql.length(), &statement, 0);
    if (rc != SQLITE_OK){
        EX_THROW(Ex_Database_Error, "Failed preparing the following sql: [" + sql + "]. Error code: " + intToStr(rc));
    }

    rc = sqlite3_step(statement);
    if (rc == SQLITE_DONE){
        // there is nothing else
        sqlite3_finalize(statement);
        return;
    } else if (rc == SQLITE_ROW){

        while(true){

            strvec columns;
            bool r = read_row(statement, columns);
            result.push_back(columns);
            if (!r) break; // that was the last one

        }

    } else {
        EX_THROW(Ex_Database_Error, "Untreated return code: " + intToStr(rc));
    }

    sqlite3_finalize(statement);

}

bool Database::read_row(sqlite3_stmt *statement, std::vector<std::string> &columns){

    int count = sqlite3_column_count(statement);
    for (int i=0; i<count; i++){

        const unsigned char *pcszCol = sqlite3_column_text(statement, i);
        int col_len = sqlite3_column_bytes(statement, i);
        ManagedBuffer mb {static_cast<unsigned int>(col_len) + 2};
        snprintf(mb.buffer, col_len+1, "%s", pcszCol);
        std::string value = mb.buffer;
        columns.push_back(value);

    }

    int rc = sqlite3_step(statement);
    if (rc == SQLITE_ROW){
        return true;
    } else if (rc == SQLITE_DONE){
        return false;
    } else {
        EX_THROW(Ex_Database_Error, "Failed fully iterating statement");
    }

}
