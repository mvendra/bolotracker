
#ifndef __DATABASE_H__
#define __DATABASE_H__

#include <string>

#include "sqlite3.h"

// this class is the system's Database Access Object

int exec_callback(void *notused, int argc, char **argv, char **col_name);

class Database final {

public:

    Database(const std::string &connection);
    ~Database();

    Database(const Database&) = delete;
    Database(Database&&) = delete;
    Database& operator=(const Database&) = delete;
    Database& operator=(Database&&) = delete;

    bool exec(const std::string &sql, std::string &return_msg);

private:

    void bootstrap();

    sqlite3 *sqlite_con;

};

#endif // __DATABASE_H__
