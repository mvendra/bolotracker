
#include "database.h"
#include "exceptions/ex_failed_opening_database.h"

int exec_callback(void *notused, int argc, char **argv, char **col_name){

    (void)notused;

    // mvtodo: finish this
    for (int i = 0; i < argc; i++){
        printf("%s = %s\n", col_name[i], argv[i] ? argv[i] : "NULL");
    }

    return 0;
}

Database::Database(const std::string &connection):sqlite_con{0}{

    int rc {sqlite3_open(connection.c_str(), &sqlite_con)};
    if (rc){
        sqlite3_close(sqlite_con);
        EX_THROW(Ex_FailedOpeningDatabase, "Failed opening the database: " + connection);
    }

}

Database::~Database(){
    sqlite3_close(sqlite_con);
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
